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
        REMOVE,
        CONFIRMCONNECTION,
        DISCONNECTION,
        DISCONNECT
    };

    enum class SendEvent : std::uint8_t
    {
        UPDATE,
        ADD,
        REMOVE,
        DEAD,
        DESCONNECTCLIENT,
    };

    enum class TCPEvent : std::uint8_t
    {
        ERROR,
        OK,
        GET_ROOMS,      // Get rooms numbers
        CONNECT,        // Connect to a room
        DISCONNECT,     // Disconnect from a room
        CREATE_ROOM,    // Create a room
        START           // Start a game inside a room
    };

    struct UDPMessage
    {
        int playerID;
        int value[10];
        Event event;
        std::uint8_t roomNbr;
    };

    struct TCPMessage
    {
        TCPEvent event;
        char data[MAX_BODY_LENGTH];
    };

    struct UDPClientMessage
    {
        SendEvent event;
        int entitieType;
        int uniqueID;
        int value[10];
        //value[0] : 1 = message à afficher, 0 = le joueur est mort
        //value[1] value[2] : position x y du sprite
        //value[3] : rotation (jsp à quoi ça sert mais Thomas l'a mis donc ça doit servir)
        //value[4] value[5] value[6] value[7] : les positions x y dans le sprite cheet et la Longueur et largeur à prendre
    };
}
#endif /* !NETCOMMON_HPP_ */
