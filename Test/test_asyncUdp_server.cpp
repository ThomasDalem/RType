/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** test_asyncUdp_server
*/

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class udp_server
{
public:
    udp_server(boost::asio::io_context &io_context)
        : socket_(io_context, udp::endpoint(udp::v4(), 8880))
    {
        start_receive();
    }

private:
    void start_receive()
    {
        socket_.async_receive_from(
            boost::asio::buffer(recv_buffer_), remote_endpoint_,
            boost::bind(&udp_server::handle_receive, this, recv_buffer_, boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive(boost::array<char, 128> buffer, const boost::system::error_code &error,
                        std::size_t len/*bytes_transferred*/)
    {
        if (!error || error == boost::asio::error::message_size)
        {
            std::cout.write(recv_buffer_.data(), len);
            boost::shared_ptr<std::string> message(
                new std::string(make_daytime_string()));

            socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
                                  boost::bind(&udp_server::handle_send, this, message,
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));

            start_receive();
        }
    }

    void handle_send(boost::shared_ptr<std::string> /*message*/,
                     const boost::system::error_code & /*error*/,
                     std::size_t /*bytes_transferred*/)
    {
        std::cout << "Sending data" << std::endl;
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 128> recv_buffer_;
};

int main()
{
    try
    {
        boost::asio::io_context io_context;
        udp_server server(io_context);
        boost::thread t(boost::bind(&boost::asio::io_context::run, &io_context));
        while (1)
        {
            sleep(1);
            std::cout << "I do my bail" << std::endl;
        }
        io_context.run();
        t.join();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}