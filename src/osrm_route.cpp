#include "routing_app.hpp"

#include <array>

using namespace osrm;

std::array<double, 4> route_osrm(double lon1, double lat1, double lon2, double lat2,
                                 const OSRM& osrm)
{

  RouteParameters params;
  // std::cout << "lat1: " << lat1 << ", lon1: " << lon1 <<
  //   ", lat2: " << lat2 << ", lon2: " << lon2 << std::endl;


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
      distance[0] = r_distance;
      distance[1] = r_duration;
      distance[2] = d1;
      distance[3] = d2;

      //std::cout << "dist: " << r_distance << ", dur: " << r_duration <<
      // ", d1: " << d1 << ", d2: " << d2 << std::endl;

      // std::cout << "Distance: " << distance << " meter\n";
      // std::cout << "Duration: " << duration << " seconds\n";
      // return 0;
    }
  else if (status == Status::Error)
    {
      const auto code = json_result.values["code"].get<json::String>().value;
      const auto message = json_result.values["message"].get<json::String>().value;

      // write out
      distance[0] = -9999.0;
      distance[1] = -9999.0;
      distance[2] = -9999.0;
      distance[3] = -9999.0;


      //std::cout << "Code: " << code << "\n";
      //std::cout << "Message: " << code << "\n";
      //return 1;
    }

    // write out
    return std::array<double, 4>{r_distance, r_duration, d1, d2};

  }

  // status == Status::Error
  // return std::array<double,4>(4, -9999.0);
  return std::array<double,4>{-9999.0,-9999.0,-9999.0,-9999.0};

}
