cmake_minimum_required(VERSION 3.10)
project(CrowApp)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add Crow as an include directory (adjust path if needed)
include_directories(/crow)

# Add the app executable
add_executable(app main.cpp)

# Link pthread library
target_link_libraries(app pthread)
