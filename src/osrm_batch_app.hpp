#ifndef OSRM_BATCH_APP_H_
#define OSRM_BATCH_APP_H_

#include "osrm/match_parameters.hpp"
#include "osrm/nearest_parameters.hpp"
#include "osrm/route_parameters.hpp"
#include "osrm/table_parameters.hpp"
#include "osrm/trip_parameters.hpp"

#include "osrm/coordinate.hpp"
#include "osrm/engine_config.hpp"
#include "osrm/json_container.hpp"

#include "osrm/osrm.hpp"
#include "osrm/status.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>

#include <exception>
#include <iostream>
#include <string>
#include <utility>
#include <ctime>

#include <cstdlib>

// #include <stdio.h>
// #include <netdb.h>
// #include <netinet/in.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <sys/types.h>

void route_osrm(double lon1, double lat1, double lon2, double lat2, const osrm::OSRM * osrm, double* distance);

// <void connection_handler(int sockfd, const osrm::OSRM *osrm);

#endif // OSRM_BATCH_APP_H_
