#include <iostream>
#include <asio.hpp>

#include "server.h"

int main() {
    try {
        asio::io_context io_context;
        Server server(io_context, PORT);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
