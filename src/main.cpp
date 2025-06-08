#include <task_scheduler/scheduler.h>
#include <iostream>
#include <string>
#include <sstream>

void printUsage() {
    std::cout << "Usage:" << std::endl;
    std::cout << "  create <priority> - Create a new task" << std::endl;
    std::cout << "  pause <id>        - Pause a task" << std::endl;
    std::cout << "  resume <id>       - Resume a task" << std::endl;
    std::cout << "  kill <id>         - Kill a task" << std::endl;
    std::cout << "  list              - List all tasks" << std::endl;
    std::cout << "  exit              - Exit the application" << std::endl;
}

int main() {
    Scheduler scheduler(4); // Create a scheduler with 4 worker threads

    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "create") {
            int priority;
            ss >> priority;
            scheduler.submit(priority, [priority]() {
                std::cout << "Running task with priority " << priority << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(5));
            });
        } else if (command == "pause") {
            int id;
            ss >> id;
            scheduler.pause(id);
        } else if (command == "resume") {
            int id;
            ss >> id;
            scheduler.resume(id);
        } else if (command == "kill") {
            int id;
            ss >> id;
            scheduler.kill(id);
        } else if (command == "list") {
            scheduler.listTasks();
        } else if (command == "exit") {
            break;
        } else {
            printUsage();
        }
    }

    return 0;
}