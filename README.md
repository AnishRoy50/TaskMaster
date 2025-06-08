# 🚀 TaskMaster

**TaskMaster** is a lightweight, multithreaded task scheduler written in modern **C++17**.  
It simulates an OS-style scheduler with real-time task management through a CLI.

---

## 🔧 Features

✨ **Multithreading** — Executes tasks concurrently using a thread pool  
📋 **Task Management** — Create, pause, resume, and kill tasks  
📊 **Priority Queue** — Tasks are sorted and executed based on priority  
🖥️ **Command-Line Interface** — Interact via simple commands like `create`, `pause`, `kill`  
📝 **Logging** — Track execution time and task states

---

## ⚙️ Build & Run

> 🧠 Prerequisites: C++17 compiler, CMake 3.10+, Git

```bash
# 🔽 Clone the repo
git clone https://github.com/AnishRoy50/TaskMaster.git
cd TaskMaster

# 🏗️ Create build directory
mkdir build && cd build

# ⚙️ Run CMake
cmake ..

# 🧱 Compile the project
cmake --build .

# ▶️ Run the executable
./TaskMaster
```

## 🧠 How It Works

### 🧩 Task Class
A `Task` encapsulates:
- Task ID
- Priority
- Function to execute
- Current state (`ready`, `paused`, `killed`)

### ⏱️ Scheduler
- Initializes a **thread pool**
- Accepts tasks via `submit()`
- Sorts tasks using a **priority queue**
- Uses `std::mutex` and `std::condition_variable` for thread-safe execution
- Each worker thread continuously picks the highest-priority task and executes it

### 💻 Main CLI
- Reads user input:
  - `create`, `list`, `pause <id>`, `resume <id>`, `kill <id>`, etc.
- Passes commands to the Scheduler for execution

---
## 📁 Project Structure

```text
TaskMaster/
├── include/
│   └── task_scheduler/
│       ├── task.h
│       └── scheduler.h
├── src/
│   ├── main.cpp
│   ├── task.cpp
│   └── scheduler.cpp
├── tests/
│   └── scheduler_tests.cpp
├── CMakeLists.txt
└── README.md
```


---

## 🚀 Ideas for Expansion

- 🧬 **Task Dependencies** — Allow tasks to depend on others
- ⏰ **Recurring Tasks** — Schedule tasks to run at regular intervals
- 💾 **Persistence** — Save and load task queue from a file
- 🖼️ **GUI** — Build a graphical interface (e.g. with Qt or ImGui)
- 📦 **REST API** — Expose task operations over HTTP using C++ REST SDK or Python FastAPI proxy

---

## 🧑‍💻 Author

Made with ❤️ by **Anish Roy**  
📫 Email: [anish.roy.official.bd@gmail.com](mailto:anish.roy.official.bd@gmail.com)
