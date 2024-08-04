#include <iostream>
#include <memory>
#include <utility>

#include "communication.h"
#include "protocol.h"
#include "session.h"

uint32_t Session::nextId = 1;

Session::Session(tcp::socket &socket)
    : m_id(nextId++)
    , m_socket(std::move(socket))
{
    std::cout << "#" << m_id << ": new connection from " << m_socket.remote_endpoint().address() << std::endl;
}

void Session::start()
{
    read();
}

void Session::read()
{
    std::shared_ptr<Session> self(shared_from_this());

    m_socket.async_read_some(asio::buffer(m_data, max_length),
        [this, self](std::error_code ec, std::size_t length) {
            if (!ec) {
                Message msg(m_data, length);

                bool readNext = Communication(msg, this).consume();
                if (readNext) {
                    read();
                } else {
                    std::cout << "#" << m_id << ": closing connection." << std::endl;
                    m_socket.close();
                }

            } else {
                std::cout << "#" << m_id << ": lost connection" << std::endl;
            }
        });
}


void Session::send(const Message &msg)
{
    m_socket.write_some(asio::buffer(msg.getData(), msg.getSize()));
}
