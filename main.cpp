#define CROW_MAIN
#include "crow.h"
#include <pqxx/pqxx>

int main()
{
	
	

    // Replace with your Render database credentials
    std::string conn_str = "host=dpg-cvbh0gtds78s73akhha0-a port=5432 dbname=test_2rgw user=test_2rgw_user password=YWybVsl153lFIN4Dy7vrO7pzeMu8z9aO";
       crow::SimpleApp app;
	   
	   
CROW_ROUTE(app, "/query").methods(crow::HTTPMethod::POST)([&](const crow::request& req) {
        try {
            // Parse the input from the request body (if needed)
            auto query_input = crow::json::load(req.body);
            if (!query_input || !query_input.has("query")) {
                return crow::response(400, "Invalid input");
            }

            // Extract the SQL query
            std::string query = query_input["query"].s();

            // Connect to the database
            pqxx::connection conn(conn_str);
            pqxx::work txn(conn);

            // Execute the query
            pqxx::result res = txn.exec(query);
            txn.commit();

            // Prepare the JSON response
            std::vector<crow::json::wvalue> rows;
            for (const auto& row : res) {
                crow::json::wvalue row_json;
                for (const auto& field : row) {
                    row_json[field.name()] = field.c_str();
                }
                rows.push_back(std::move(row_json));
            }

            crow::json::wvalue json_res;
            json_res["rows"] = std::move(rows); // Convert vector to JSON array

            return crow::response(json_res);
        } catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
    });
	

    // Define a simple route
    CROW_ROUTE(app, "/")([]() {
        return "Hello, World! This is a C++ app hosted on Render.";
    });

    // Start the server
    app.port(8080).multithreaded().run();
    return 0;
}
