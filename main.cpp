#define CROW_MAIN
#include "crow.h"
#include <pqxx/pqxx>

#include <fstream>
#include <string>

std::string ReadFile(const std::string& filePath)
{
    std::ifstream file(filePath, std::ios::in | std::ios::binary); // Open in binary mode for any type of file
    if (file)
	{
        return std::string((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>()); // Read whole content
    }
    throw std::ios_base::failure("Error: Unable to open file " + filePath);
}

void HeartbeatsThread() try
{
	const std::string conn_str = ReadFile("/etc/secrets/database_conn_str");
	pqxx::connection conn(conn_str);
    while (true)
	{
		pqxx::work txn(conn);

		txn.exec(
			"UPDATE sessions "
			"SET is_active = FALSE "
			"WHERE last_heartbeat < NOW() - INTERVAL '3 minutes' AND is_active = TRUE"
		);

		txn.commit();
		std::cout << "Heartbeat monitoring: Expired inactive sessions." << std::endl;

        std::this_thread::sleep_for(std::chrono::minutes(1));
    }
}
catch (const std::exception& e)
{
	std::cerr << "Error in heartbeat monitoring: " << e.what() << std::endl;
}

int main()
{
	const std::string conn_str = ReadFile("/etc/secrets/database_conn_str");
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

    std::thread heartbeatThread(HeartbeatsThread);
    heartbeatThread.detach();

    // Start the server
    app.port(8080).multithreaded().run();
    return 0;
}
