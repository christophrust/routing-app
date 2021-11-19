#include "osrm/engine_config.hpp"
#include "osrm/osrm.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <iostream>


#include "routing_app.hpp"

using boost::asio::ip::tcp;

using namespace osrm;

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " data.osrm\n";
        return EXIT_FAILURE;
    }

    std::string port = argv[2];

    // Configure based on a .osrm base path, and no datasets in shared mem from osrm-datastore
    EngineConfig config;

    config.storage_config = {argv[1]};
    config.use_shared_memory = false;

    // We support two routing speed up techniques:
    // - Contraction Hierarchies (CH): requires extract+contract pre-processing
    // - Multi-Level Dijkstra (MLD): requires extract+partition+customize pre-processing
    //
    config.algorithm = EngineConfig::Algorithm::CH;
    //config.algorithm = EngineConfig::Algorithm::MLD;

    // Routing machine with several services (such as Route, Table, Nearest, Trip, Match)
    std::cout << "Preparing OSRM instance..." << std::endl;
    const OSRM osrm{config};


    std::cout << "Binding application to 127.0.0.1:" << port << std::endl;
    try
    {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), std::stoul(port)));

        // double distance[4]{};

        for (;;)
        {

            try
            {
                tcp::socket socket(io_context);
                acceptor.accept(socket);

                // use simple protocol
                // read first 16 bytes of stream, giving us the length of the body
                std::vector<std::size_t> stream_size {0};
                boost::asio::read(socket, boost::asio::buffer(stream_size));

                std::vector<double> data(stream_size[0]);
                std::vector<double> result_data(stream_size[0]);

                boost::asio::read(socket, boost::asio::buffer(data));


                /* Here goes all the heavy lifting to osrm */
                const auto n_request = stream_size[0] / 4;

                for (size_t i = 0; i < n_request; ++i)
                {

                    const auto lat_src = data[i];
                    const auto lon_src = data[i + n_request];
                    const auto lat_dst = data[i + 2*n_request];
                    const auto lon_dst = data[i + 3*n_request];

                    //std::cout << "lat1: " << lat_src << ", lon1: " << lon_src <<
                    //    ", lat2: " << lat_dst << ", lon2: " << lon_dst << std::endl;
                    const auto distance = route_osrm(lon_src, lat_src, lon_dst, lat_dst, osrm);

                    result_data[i] = distance[0];
                    result_data[i + n_request] = distance[1];
                    result_data[i + 2 * n_request] = distance[2];
                    result_data[i + 3 * n_request] = distance[3];
                }

                boost::system::error_code ignored_error;
                boost::asio::write(socket, boost::asio::buffer(result_data), ignored_error);
            }
            catch (std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
        // boost::system::error_code ignored_error;
        // boost::asio::write(socket, boost::asio::buffer(message), ignored_error);

    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;

}


