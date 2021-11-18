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
      tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8081));

      for (;;)
        {


          tcp::socket socket(io_context);
          acceptor.accept(socket);

          // use simple protocol
          // read first 4 bytes of stream, giving us the length of the body
          std::vector<std::size_t> stream_size(1);
          boost::asio::read(socket, boost::asio::buffer(stream_size));

          std::vector<double> data(stream_size[0]);
          boost::asio::read(socket, boost::asio::buffer(data));

          for (size_t i=0; i < stream_size[0]; i++){
            std::cout << data[i] << std::endl;
          }
          for (size_t i=0; i < stream_size[0]; i++){
            data[i] = data[i]/2.0;
          }
          boost::system::error_code ignored_error;
          boost::asio::write(socket, boost::asio::buffer(data), ignored_error);
        }
      // boost::system::error_code ignored_error;
      // boost::asio::write(socket, boost::asio::buffer(message), ignored_error);

    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  return 0;
}
