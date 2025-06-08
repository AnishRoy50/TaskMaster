#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <map>

class Scheduler {
public:
    Scheduler(size_t numThreads);
    ~Scheduler();

    void submit(int priority, std::function<void()> func);
    void pause(int taskId);
    void resume(int taskId);
    void kill(int taskId);
    void listTasks();

private:
    void worker();

    struct TaskComparator {
        bool operator()(const Task* a, const Task* b) {
            return a->priority < b->priority;
        }
    };

    std::priority_queue<Task*, std::vector<Task*>, TaskComparator> taskQueue;
    std::map<int, Task*> tasks;

    std::vector<std::thread> workers;
    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
    std::atomic<int> nextTaskId;

    std::mutex taskMapMutex;
};

#endif // SCHEDULER_H