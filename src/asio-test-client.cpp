#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>


using boost::asio::ip::tcp;
int main()
{
  try
    {
      boost::asio::io_context io_context;
      tcp::resolver resolver(io_context);

      tcp::resolver::results_type endpoints =
        resolver.resolve("127.0.0.1", "8081");

      tcp::socket socket(io_context);
      boost::asio::connect(socket, endpoints);

      std::vector<size_t> stream_size(1);
      std::vector<double> data = {12.222,123.2232,1232.2222};
      stream_size[0] = data.size();

      boost::asio::write(socket, boost::asio::buffer(stream_size));
      boost::asio::write(socket, boost::asio::buffer(data));

    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  return 0;
}
