cmake_minimum_required(VERSION 3.10)
project(TaskMaster)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the threads library package; this is required for std::thread, etc.
# This command creates the "Threads::Threads" imported target.
find_package(Threads REQUIRED)

# Define the executable with its source files
add_executable(TaskMaster main.cpp scheduler.cpp task.cpp)

# Add the current source directory to the include path so that
# #include "scheduler.h" and #include "task.h" can be found.
target_include_directories(TaskMaster PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link the executable against the threads library.
# This is now cross-platform and will work on Windows, Linux, and macOS.
target_link_libraries(TaskMaster PRIVATE Threads::Threads)