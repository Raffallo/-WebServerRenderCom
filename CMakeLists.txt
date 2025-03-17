cmake_minimum_required(VERSION 3.10)
project(CrowApp)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include Crow, ASIO, and pqxx directories
include_directories(/crow/include /asio/asio/include)

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

# Link pqxx library
find_package(PQXX REQUIRED)
if(PQXX_FOUND)
    include_directories(${PQXX_INCLUDE_DIRS})
    target_link_libraries(app pqxx pq)
endif()
