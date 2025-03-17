#define CROW_MAIN
#include "crow.h"
#include <pqxx/pqxx>

int main() {
	
	
    try {
        // Replace with your Render database credentials
        std::string conn_str = "host=postgresql://test_2rgw_user:YWybVsl153lFIN4Dy7vrO7pzeMu8z9aO@dpg-cvbh0gtds78s73akhha0-a/test_2rgw port=5432 dbname=test_2rgw user=test_2rgw_user password=YWybVsl153lFIN4Dy7vrO7pzeMu8z9aO";
        pqxx::connection conn(conn_str);

        if (conn.is_open())
		{
            std::cout << "Connected to the database successfully!" << std::endl;
        }
		else
		{
            std::cerr << "Failed to connect to the database." << std::endl;
            return 1;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    
	
    crow::SimpleApp app;

    // Define a simple route
    CROW_ROUTE(app, "/")([]() {
        return "Hello, World! This is a C++ app hosted on Render.";
    });

    // Start the server
    app.port(8080).multithreaded().run();
    return 0;
}
