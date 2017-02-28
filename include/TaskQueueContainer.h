//
// Created by Administrator on 2017/2/28 0028.
//

#ifndef CORE_TASKCONTAINER_H
#define CORE_TASKCONTAINER_H

namespace TBAS
{
    namespace Core
    {
        class TaskQueueContainer
        {
        public:
            TaskQueueContainer(CoreThreadPool* pThreadPool);
            ~TaskQueueContainer();
            std::vector<TaskQueue*>::size_type Size();
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

#endif //CORE_TASKCONTAINER_H
