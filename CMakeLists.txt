cmake_minimum_required(VERSION 3.10)
project(TaskMaster)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find threads
find_package(Threads REQUIRED)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Source files
set(SOURCES
    src/main.cpp
    src/scheduler.cpp
    src/task.cpp
)

# Header files (not strictly necessary to list unless for IDEs)
set(HEADERS
    include/task_scheduler/scheduler.h
    include/task_scheduler/task.h
)

# Create the executable
add_executable(TaskMaster ${SOURCES} ${HEADERS})

# Link threads
target_link_libraries(TaskMaster PRIVATE Threads::Threads)

# Optional: Add test executable (if needed)
# Enable testing and add executable for test
enable_testing()
add_executable(TaskMasterTests tests/scheduler_tests.cpp)
target_include_directories(TaskMasterTests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(TaskMasterTests PRIVATE Threads::Threads)
add_test(NAME SchedulerTests COMMAND TaskMasterTests)
