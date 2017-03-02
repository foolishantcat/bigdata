//
// Created by Administrator on 2017/2/28 0028.
//

#ifndef TASK_QUEUE_CONTAINER_H
#define TASK_QUEUE_CONTAINER_H

#include <vector>
#include "TaskQueue.h"

namespace TBAS
{
    namespace Core
    {
		class CoreThreadPool;
        class TaskQueueContainer
        {
        public:
            TaskQueueContainer(CoreThreadPool* pThreadPool);
            ~TaskQueueContainer();
            unsigned int Size();
            void Assign(int number, TaskQueueContainer* pContainer);
            TaskQueue* At(int index);

        private:
            std::vector<TaskQueue*> task_queue_container_;
            void Push(TaskQueue* pQueue);
            void Erase(TaskQueue* pQueue);
            typedef std::vector<TaskQueue*> Container;
            typedef Container::iterator Iterator;
            int number_of_task_queue_;
            CoreThreadPool* thread_pool_;
        };
    }
}

#endif //TASK_QUEUE_CONTAINER_H
