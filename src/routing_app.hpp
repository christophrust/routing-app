#ifndef ROUTING_APP_H_
#define ROUTING_APP_H_

#include "osrm/osrm.hpp"
#include <array>

std::array<double, 4> route_osrm(double lon1, double lat1, double lon2, double lat2,
                                 const osrm::OSRM&);

#endif // ROUTING APP_H_
