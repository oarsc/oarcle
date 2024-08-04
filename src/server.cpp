#include <memory>

#include "server.h"

Server::Server(asio::io_context& io_context, uint16_t port)
    : m_acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
    doAccept();
}

void Server::doAccept()
{
    m_acceptor.async_accept(
        [this](std::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(socket)->start();
            }
            doAccept();
        });
}
