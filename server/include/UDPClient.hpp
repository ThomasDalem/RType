/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** UDPClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include <boost/asio.hpp>
#include "NetCommon.hpp"

class UDPClient {
public:
    UDPClient(int id, boost::asio::ip::udp::endpoint &endpoint);
    UDPClient(UDPClient const& other);
    ~UDPClient();

    bool isConnected() const;
    boost::asio::ip::udp::endpoint const& getEndpoint() const;

    UDPClient &operator=(UDPClient const& other);

private:
    int _id;
    bool _isConnected;
    boost::asio::ip::udp::endpoint _endpoint;
};

#endif /* !UDPCLIENT_HPP_ */
