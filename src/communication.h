#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <iostream>

#include "message.h"
#include "session.h"

class Communication {
public:
    Communication(Message &msg, Session* session);

    bool consume();

private:
    void runCommand();

    Message &m_msg;
    Session* m_session;
};

#endif // COMMUNICATION_H