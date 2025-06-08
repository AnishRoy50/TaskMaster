#ifndef TASK_H
#define TASK_H

#include <functional>
#include <chrono>

enum class TaskStatus {
    QUEUED,
    RUNNING,
    PAUSED,
    COMPLETED,
    KILLED
};

class Task {
public:
    int id;
    int priority;
    TaskStatus status;
    std::function<void()> function;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point endTime;

    Task(int id, int priority, std::function<void()> func);

    double getExecutionTime() const;
};

#endif // TASK_H