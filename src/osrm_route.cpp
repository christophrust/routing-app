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



using namespace osrm;

void route_osrm(double lon1, double lat1, double lon2, double lat2, const OSRM * osrm, double* result){

  RouteParameters params;

  //
  params.coordinates.push_back({util::FloatLongitude{lon1}, util::FloatLatitude{lat1}});
  params.coordinates.push_back({util::FloatLongitude{lon2}, util::FloatLatitude{lat2}});

  // Response is in JSON format
  engine::api::ResultT result = json::Object();

  // Execute routing request, this does the heavy lifting
  const auto status = osrm->Route(params, result);

  auto &json_result = result.get<json::Object>();
  if (status == Status::Ok)
    {

      // get first route
      auto &routes = json_result.values["routes"].get<json::Array>();
      auto &route = routes.values.at(0).get<json::Object>();
      const auto distance = route.values["distance"].get<json::Number>().value;
      const auto duration = route.values["duration"].get<json::Number>().value;

      // and distance from input coordinates to waypoints
      auto &waypoints = json_result.values["waypoints"].get<json::Array>();
      auto &waypoint1 = waypoints.values.at(0).get<json::Object>();
      auto &waypoint2 = waypoints.values.at(1).get<json::Object>();
      const auto d1 = waypoint1.values["distance"].get<json::Number>().value;
      const auto d2 = waypoint2.values["distance"].get<json::Number>().value;

      // write out
      result[0] = distance;
      result[1] = duration;
      result[2] = d1;
      result[3] = d2;


      // std::cout << "Distance: " << distance << " meter\n";
      // std::cout << "Duration: " << duration << " seconds\n";
      // return 0;
    }
  else if (status == Status::Error)
    {
      const auto code = json_result.values["code"].get<json::String>().value;
      const auto message = json_result.values["message"].get<json::String>().value;

      // write out
      result[0] = -9999.0;
      result[1] = -9999.0;
      result[2] = -9999.0;
      result[3] = -9999.0;


      //std::cout << "Code: " << code << "\n";
      //std::cout << "Message: " << code << "\n";
      //return 1;
    }

}
