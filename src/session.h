#ifndef SESSION_H
#define SESSION_H

#include <memory>
#include <asio.hpp>

#include "consts.h"
#include "message.h"

using asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket &socket);
    void start();

    void send(const Message &msg);
    uint32_t getId() const { return m_id; }

private:
    void read();

    uint32_t m_id;
    tcp::socket m_socket;
    enum { max_length = MAX_MESSAGE_SIZE };
    uint8_t m_data[max_length];

    static uint32_t nextId;
};

#endif // SESSION_H