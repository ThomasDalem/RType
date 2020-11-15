/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** UDPClient
*/

#include "UDPClient.hpp"

UDPClient::UDPClient(int id, boost::asio::ip::udp::endpoint &endpoint) : _id(id), _endpoint(endpoint)
{
}

UDPClient::UDPClient(UDPClient const& other) : _id(other._id), _endpoint(other._endpoint), _isConnected(other._isConnected)
{
}

UDPClient::~UDPClient()
{
}

boost::asio::ip::udp::endpoint const& UDPClient::getEndpoint() const
{
    return _endpoint;
}

UDPClient &UDPClient::operator=(UDPClient const& other)
{
    _id = other._id;
    _endpoint = other._endpoint;
    _isConnected = other._isConnected;
}


