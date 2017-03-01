//
// Created by Administrator on 2017/2/27 0027.
//

#ifndef TASK_QUQUE_H
#define TASK_QUQUE_H

#include <list>
#include <memory>
#include "IASObject.h"

namespace TBAS
{
    namespace Core
    {
		class TaskQueueContainer;
        class TaskQueue
        {
        public:
            TaskQueue(TaskQueueContainer* container);
            ~TaskQueue();
            unsigned int Size();
            void Push(std::weak_ptr<IASObject> asObject);
            std::weak_ptr<IASObject> Top();
            void Pop();
            bool Empty();
            //std::list<std::week_ptr<IASObject>> GetTaskList();
            std::list<std::weak_ptr<IASObject>> object_list_;

        private:
            int number_of_task_;
            TaskQueueContainer* task_queue_container_;
        };
    }
}

#endif //CORE_OBJECTCONTAINER_H
