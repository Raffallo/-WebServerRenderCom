#include "crow.h"

int main() {
    crow::SimpleApp app;

    // Define a simple route
    CROW_ROUTE(app, "/")([]() {
        return "Hello, World! This is a C++ app hosted on Render.";
    });

    // Start the server
    app.port(8080).multithreaded().run();

    return 0;
}
