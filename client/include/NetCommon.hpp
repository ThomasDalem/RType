/*
** EPITECH PROJECT, 2020
** boost_asio_test
** File description:
** NetCommon
*/

#ifndef NETCOMMON_HPP_
#define NETCOMMON_HPP_

#include <cstdint>
#include <boost/asio.hpp>

#define MAX_MESSAGE_LENGTH 1024
#define MAX_BODY_LENGTH 1024

namespace network
{
    enum class Event : std::uint8_t
    {
        MOVE,
        SHOOT,
        ADD,
        REMOVE
    };

    enum class TCPEvent : std::uint8_t
    {
        CONNECT,
        DISCONNECT,
        START
    };

    struct UDPMessage
    {
        int playerID;
        int value[10];
        Event event;
    };

    struct TCPMessage
    {
        TCPEvent event;
        char data[MAX_BODY_LENGTH];
    };

    struct UDPClientMessage
    {
        int entitieType;
        int uniqueID;
        int pos[5];
        float rotation;
        int spriteRectangle[10];
    };
}
#endif /* !NETCOMMON_HPP_ */
