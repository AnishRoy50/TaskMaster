#include "task_scheduler/scheduler.h"
#include <iostream>
#include <utility>

Scheduler::Scheduler(size_t numThreads) : stop(false), nextTaskId(1) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back(&Scheduler::worker, this);
    }
}

Scheduler::~Scheduler() {
    stop = true;
    condition.notify_all();
    for (std::thread &worker : workers) {
        worker.join();
    }
}

void Scheduler::worker() {
    while (!stop) {
        Task* task = nullptr;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return !taskQueue.empty() || stop; });

            if (stop && taskQueue.empty()) {
                return;
            }

            task = taskQueue.top();
            taskQueue.pop();
        }

        if (task) {
            if (task->status != TaskStatus::KILLED) {
                task->status = TaskStatus::RUNNING;
                task->startTime = std::chrono::steady_clock::now();

                task->function();

                task->status = TaskStatus::COMPLETED;
                task->endTime = std::chrono::steady_clock::now();
            }
        }
    }
}

void Scheduler::submit(int priority, std::function<void()> func) {
    int taskId = nextTaskId++;
    Task* newTask = new Task(taskId, priority, std::move(func));

    {
        std::unique_lock<std::mutex> lock(taskMapMutex);
        tasks[taskId] = newTask;
    }

    {
        std::unique_lock<std::mutex> lock(queueMutex);
        taskQueue.push(newTask);
    }
    condition.notify_one();
    std::cout << "Task " << taskId << " created." << std::endl;
}

void Scheduler::pause(int taskId) {
    std::unique_lock<std::mutex> lock(taskMapMutex);
    if (tasks.count(taskId)) {
        tasks[taskId]->status = TaskStatus::PAUSED;
        std::cout << "Task " << taskId << " paused." << std::endl;
    }
}

void Scheduler::resume(int taskId) {
    std::unique_lock<std::mutex> lock(taskMapMutex);
    if (tasks.count(taskId)) {
        tasks[taskId]->status = TaskStatus::QUEUED;
        condition.notify_one();
        std::cout << "Task " << taskId << " resumed." << std::endl;
    }
}

void Scheduler::kill(int taskId) {
    std::unique_lock<std::mutex> lock(taskMapMutex);
    if (tasks.count(taskId)) {
        tasks[taskId]->status = TaskStatus::KILLED;
        std::cout << "Task " << taskId << " killed." << std::endl;
    }
}

void Scheduler::listTasks() {
    std::unique_lock<std::mutex> lock(taskMapMutex);
    std::cout << "ID\tPriority\tStatus\t\tTime Taken (s)" << std::endl;
    for (const auto& pair : tasks) {
        Task* task = pair.second;
        std::cout << task->id << "\t" << task->priority << "\t\t";
        switch (task->status) {
            case TaskStatus::QUEUED: std::cout << "QUEUED"; break;
            case TaskStatus::RUNNING: std::cout << "RUNNING"; break;
            case TaskStatus::PAUSED: std::cout << "PAUSED"; break;
            case TaskStatus::COMPLETED: std::cout << "COMPLETED"; break;
            case TaskStatus::KILLED: std::cout << "KILLED"; break;
        }
        std::cout << "\t\t" << task->getExecutionTime() << std::endl;
    }
}