#include "osrm_batch_app.hpp"
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

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

    boost::asio::io_context io_context;
            tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), std::stoul(port)));
    /*
    try
        {
            boost::asio::io_context io_context;
            tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), std::stoul(port)));
            for (;;)
                {
                    tcp::socket socket(io_context);
                    acceptor.accept(socket);
                    std::string message = "Blablub!";
                    std::cout << "New connection!" << std::endl;

                    boost::system::error_code ignored_error;
                    boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
                }
        } catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }

    */

    if (0){
        std::cout << "Waiting for requests...:" << std::endl;
        double lat_src, lon_src, lat_dst, lon_dst;
        lat_src = 46.3434;
        lon_src = 14.2322;
        lat_dst = 47.2222;
        lon_dst = 15.2322;

        double distance[4];
        route_osrm(lon_src, lat_src, lon_dst, lat_dst, &osrm, distance);

        std::cout << "Distance:" << distance[0] << std::endl;

    }

    return EXIT_SUCCESS;

}


