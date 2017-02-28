//
// Created by Administrator on 2017/2/28 0028.
//

#include "TaskQueue.h"
#include "TaskQueueContainer.h"

TaskQueueContainer::TaskQueueContainer(CoreThreadPool* pThreadPool)
{
    task_queue_container_.clear();
    number_of_task_queue_ = 0;
    thread_pool_ = pThreadPool;
}

TaskQueueContainer::~TaskQueueContainer()
{
    for(Iterator it = task_queue_container_.begin();
        it != task_queue_container_.end();
        it++)
    {
        cout << i++ << endl;
        delete *it;
    }
}

void TaskQueueContainer::Assign(int number, TaskQueueContainer* container)
{
    for (int i = 0; i < number; i++)
    {
        TaskQueue* taskQueue = new TaskQueue(container);
        Push(taskQueue);
    }
}

void TaskQueueContainer::Push(TaskQueue* pQueue)
{
    task_queue_container_.push_back(pQueue);
}

TaskQueue* TaskQueueContainer::At(int index)
{
    return task_queue_container_.at(index);
}

void TaskQueueContainer::Erase(TaskQueue* pQueue)
{
    task_queue_container_.erase(std::find(task_queue_container_.begin(), task_queue_container_, pQueue));
}
