/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** test_upd
*/

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <deque>

using boost::asio::ip::udp;

class udp_clientSender
{
public:
  udp_clientSender(boost::asio::io_context &io_context)
      : io_service(io_context), socket(io_context)
  {

    udp::resolver resolver(io_context);
    server_endpoint =
        *resolver.resolve(udp::v4(), "0.0.0.0", "8880").begin();
    socket.open(udp::v4());
    send_message();
  }

  ~udp_clientSender()
  {
    socket.close();
  }

private:
  void send_message()
  {
    sleep(2);
    boost::shared_ptr<std::string> message(
        new std::string("Client Message\n"));
    socket.async_send_to(boost::asio::buffer(*message), server_endpoint,
                         boost::bind(&udp_clientSender::handle_send, this, message,
                                     boost::asio::placeholders::error,
                                     boost::asio::placeholders::bytes_transferred));
  }
  void handle_send(boost::shared_ptr<std::string> /*message*/,
                   const boost::system::error_code & /*error*/,
                   std::size_t /*bytes_transferred*/)
  {
    std::cout << "Sending data" << std::endl;
    send_message();
  }
  udp::socket socket;
  udp::endpoint server_endpoint;
  boost::asio::io_context &io_service;
};

class udp_clientReceiver
{
public:
  udp_clientReceiver(boost::asio::io_context &io_context)
      : io_service(io_context), socket(io_context)
  {

    udp::resolver resolver(io_context);
    udp::endpoint receiver_endpoint =
        *resolver.resolve(udp::v4(), "0.0.0.0", "daytime").begin();

    socket.open(udp::v4());
    boost::array<char, 1> send_buf = {{0}};
    socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);
    recv_message();
  }

  ~udp_clientReceiver()
  {
    socket.close();
  }

private:
  void recv_message()
  {
    socket.async_receive_from(
        boost::asio::buffer(recv_buffer_), sender_endpoint,
        boost::bind(&udp_clientReceiver::handle_receive, this, boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
  }
  void handle_receive(const boost::system::error_code &error,
                      std::size_t len)
  {
    std::cout << "Receiving data" << std::endl;
    recv_message();
  }
  udp::socket socket;
  boost::array<char, 1> recv_buffer_;
  udp::endpoint sender_endpoint;
  boost::asio::io_context &io_service;
};

int main(int argc, char *argv[])
{
  try
  {
    boost::asio::io_context io_context;
    boost::asio::io_context io_service;
    udp_clientSender clientSender(io_context);
    udp_clientReceiver clientReceiver(io_service);
    boost::thread t(boost::bind(&boost::asio::io_context::run, &io_context));
    boost::thread t1(boost::bind(&boost::asio::io_context::run, &io_service));

    while (1)
    {
      sleep(1);
      std::cout << "I do my bail" << std::endl;
    }
    io_context.run();
    io_service.run();
    t.join();
    t1.join();
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}

// try
// {
//   if (argc != 2)
//   {
//     std::cerr << "Usage: client <host>" << std::endl;
//     return 1;
//   }

//   boost::asio::io_context io_context;

//   udp::resolver resolver(io_context);
//   udp::resolver::query query(udp::v4(), "0.0.0.0", "8888");
//   udp::endpoint *receiver_endpoint = new udp::endpoint(*resolver.resolve(query));
//   //*resolver.resolve(udp::v4(), argv[1], "daytime").begin();

//   udp::socket socket(io_context);
//   socket.open(udp::v4());

//   boost::array<char, 1> send_buf = {{0}};
//   socket.send_to(boost::asio::buffer(send_buf), *receiver_endpoint);

//   boost::array<char, 128> recv_buf;
//   udp::endpoint sender_endpoint;
//   size_t len = socket.receive_from(
//       boost::asio::buffer(recv_buf), sender_endpoint);

//   std::cout.write(recv_buf.data(), len);
// }
// catch (std::exception &e)
// {
//   std::cerr << e.what() << std::endl;
// }
