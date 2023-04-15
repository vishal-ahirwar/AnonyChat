

// Auto Genrated C++ file by newton CLI
#include "../include/crow_all.h"

int main(int argc, char *argv[])
{
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")
    ([]()
     { return "<h1>Chat Server...</h1>"; });
    char *port = getenv("PORT");
    uint16_t iport = static_cast<uint16_t>(port ? std::stoi(port) : 8080);
    app.port(iport).multithreaded().run();
    return 0;
};
