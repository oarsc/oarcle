#ifndef SERVER_H
#define SERVER_H

#include <asio.hpp>

const long long PORT = 1130;

#include "session.h"

using asio::ip::tcp;

class Server {
public:
    Server(asio::io_context& io_context, uint16_t port);

private:
    void doAccept();
    tcp::acceptor m_acceptor;
};

#endif // SERVER_H