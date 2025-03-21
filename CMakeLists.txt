cmake_minimum_required(VERSION 3.10)
project(CrowApp)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include Crow and ASIO directories
include_directories(/crow/include /asio/asio/include)

# Include libpqxx headers
include_directories(/usr/local/include)

# Add the executable
add_executable(app main.cpp)

# Link Boost libraries
find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(app ${Boost_LIBRARIES})
endif()

# Link pthread library
target_link_libraries(app pthread)

# Link libpqxx and libpq directly
target_link_libraries(app pqxx pq)
