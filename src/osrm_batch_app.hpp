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

#include <exception>
#include <iostream>
#include <string>
#include <utility>

#include <cstdlib>

void route_osrm(double lon1, double lat1, double lon2, double lat2, const osrm::OSRM * osrm, double* distance);


#endif // OSRM_BATCH_APP_H_
