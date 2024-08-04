#include <iomanip>
#include <iostream>

#include "communication.h"
#include "protocol.h"

Communication::Communication(Message &msg, Session* session)
    :m_msg(msg), m_session(session) {}

bool Communication::consume()
{
    uint8_t opt = m_msg.readU8();

    std::cout << "#" << m_session->getId() << ": opt 0x"
        << std::hex << std::uppercase
        << std::setw(2) << std::setfill('0')
        << (int)opt << std::endl;

    try {
        switch (opt) {
            case CMD: 
                runCommand();
                break;

            case CLOSE:
                return false;
        }
    } catch (const std::invalid_argument &e) {
        std::cout << "#" << m_session->getId() << " error: " << e.what() << std::endl;
        return false;
    }

    return true;
}


void Communication::runCommand()
{
    std::string cmd = m_msg.readString();
    bool hasNext = m_msg.readU8() == 1;

    std::cout << "MESSAGE RECEIVED: \"" << cmd << "\" HAS_NEXT: " << (int)hasNext << std::endl;

    Message msgOutput;
    msgOutput.writeString(cmd);
    m_session->send(msgOutput);
}