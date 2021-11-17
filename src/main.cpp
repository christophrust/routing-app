#include "osrm_batch_app.hpp"

using namespace osrm;

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " data.osrm\n";
        return EXIT_FAILURE;
    }

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
    const OSRM osrm{config};

    // The following shows how to use the Route service; configure this service

    // std::ifstream in(argv[2]);

    // std::string str;
    // std::vector<std::string> strs;


    double lat_src, lon_src, lat_dst, lon_dst;
    lat_src = 46.3434;
    lon_src = 14.2322;
    lat_dst = 47.2222;
    lon_dst = 15.2322;

    double distance[4];
    route_osrm(lon_src, lat_src, lon_dst, lat_dst, &osrm, distance);

    std::cout << "Distance:" << distance[0] << std::endl;

    return EXIT_SUCCESS;


}
