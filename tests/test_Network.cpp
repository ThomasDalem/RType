#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "NetTCPClient.hpp"
#include "NetUDPClient.hpp"

using namespace std;
// using namespace client;
static void redirect_all_std(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(Network, UDP, .init = redirect_all_std) {
    network::NetUDPClient serv("127.0.0.1", "8081");
    network::UDPMessage message = {0, 0, 0};
    network::NetUDPClient udp("127.0.0.1", "8081");

    cr_assert(!udp.hasMessages());
    serv.sendMessage(message);
    cr_assert(udp.hasMessages());
    if (udp.hasMessages())
        unique_ptr<network::UDPClientMessage> received = udp.getFirstMessage();
}

// Test(Network, TCP, .init = redirect_all_std) {
//     network::NetTCPClient serv("127.0.0.1", "8081");
//     network::TCPMessage message = {network::TCPEvent::START, {0}};
//     network::NetTCPClient tcp("127.0.0.1", "8081");

//     cr_assert(!tcp.hasMessages());
//     serv.sendMessage(message);
//     cr_assert(tcp.hasMessages());
//     if (tcp.hasMessages())
//         unique_ptr<network::UDPClientMessage> received = tcp.getFirstMessage();
// }

// void connect(void);
// void receiveMessage(void);
// bool isConnected(void) const;
// void sendMessage(TCPMessage const &message);
// unique_ptr<TCPMessage> getFirstMessage(void);
// void handleMessage(boost::system::error_code ec, size_t receivedBytes);
