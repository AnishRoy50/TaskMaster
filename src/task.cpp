#include "task.h"

Task::Task(int id, int priority, std::function<void()> func)
    : id(id), priority(priority), status(TaskStatus::QUEUED), function(std::move(func)) {}

double Task::getExecutionTime() const {
    if (status == TaskStatus::COMPLETED) {
        return std::chrono::duration<double>(endTime - startTime).count();
    }
    return 0.0;
}