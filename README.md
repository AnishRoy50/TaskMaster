# TaskMaster

A multithreaded task scheduler written in C++.

## Features

- **Task Management**: Create, pause, resume, and kill tasks.
- **Priority Queue**: Tasks are executed based on their priority.
- **Thread Pool**: A pool of worker threads executes tasks concurrently.
- **Command-Line Interface**: Interact with the scheduler through a simple CLI.
- **Logging**: Basic logging of task status and execution time.

## How to Build

```bash
# 1. Go into your project folder
cd path/to/your/TaskMaster

# 2. Create and enter a build directory
mkdir build
cd build

# 3. Configure with CMake
cmake ..

# 4. Compile
cmake --build .

# 5. Run
./TaskMaster
```
### How It All Works

1.  **Task**: The `Task` class is a simple container for task data.
2.  **Scheduler**:
    * The `Scheduler` creates a pool of worker threads upon construction.
    * The `submit` function adds a new task to a priority queue.
    * Each `worker` thread continuously picks the highest-priority task from the queue and executes it.
    * A `std::mutex` and `std::condition_variable` are used to ensure thread-safe access to the task queue.
3.  **Main**: The `main` function provides a loop to read user commands and call the appropriate `Scheduler` methods.

This implementation gives you a solid foundation. You can expand it with more advanced features like:

* **Dependencies**: Allow tasks to depend on other tasks.
* **Recurring Tasks**: Schedule tasks to run at regular intervals.
* **GUI**: Create a graphical user interface for easier task management.
* **Persistence**: Save and load tasks from a file.