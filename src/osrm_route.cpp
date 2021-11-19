#include "routing_app.hpp"

#include "osrm/route_parameters.hpp"

#include <array>

using namespace osrm;

std::array<double, 4> route_osrm(double lon1, double lat1, double lon2, double lat2,
                                 const OSRM& osrm)
{

  RouteParameters params;


  params.coordinates.push_back({util::FloatLongitude{lon1}, util::FloatLatitude{lat1}});
  params.coordinates.push_back({util::FloatLongitude{lon2}, util::FloatLatitude{lat2}});

  // Response is in JSON format
  engine::api::ResultT result = json::Object();

  // Execute routing request, this does the heavy lifting
  const auto status = osrm.Route(params, result);

  auto &json_result = result.get<json::Object>();
  if (status == Status::Ok)
  {

    // get first route
    auto &routes = json_result.values["routes"].get<json::Array>();
    auto &route = routes.values.at(0).get<json::Object>();
    const auto r_distance = route.values["distance"].get<json::Number>().value;
    const auto r_duration = route.values["duration"].get<json::Number>().value;

    // and distance from input coordinates to waypoints
    auto &waypoints = json_result.values["waypoints"].get<json::Array>();
    auto &waypoint1 = waypoints.values.at(0).get<json::Object>();
    auto &waypoint2 = waypoints.values.at(1).get<json::Object>();
    const auto d1 = waypoint1.values["distance"].get<json::Number>().value;
    const auto d2 = waypoint2.values["distance"].get<json::Number>().value;

    // write out
    return std::array<double, 4>{r_distance, r_duration, d1, d2};

  }

  // status == Status::Error
  // return std::array<double,4>(4, -9999.0);
  return std::array<double,4>{-9999.0,-9999.0,-9999.0,-9999.0};

}
