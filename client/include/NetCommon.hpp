/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** NetCommon
*/

#ifndef NETCOMMON_HPP_
#define NETCOMMON_HPP_

#include <cstdint>
#include <boost/asio.hpp>

#define MAX_MESSAGE_LENGTH 1024

namespace network
{
    enum class Event : std::uint8_t
    {
        MOVE,
        SHOOT,
        ADD,
        REMOVE
    };

    struct UDPMessage
    {
        int playerID;
        int value;
        Event event;
    };
}
#endif /* !NETCOMMON_HPP_ */
