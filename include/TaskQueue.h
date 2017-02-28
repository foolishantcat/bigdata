//
// Created by Administrator on 2017/2/27 0027.
//

#ifndef CORE_OBJECTCONTAINER_H
#define CORE_OBJECTCONTAINER_H

#include <list>
#include "IASObject.h"
#include "TaskQueueContainer.h"

namespace TBAS
{
    namespace Core
    {
        class TaskQueue
        {
        public:
            TaskQueue(TaskQueueContainer* container);
            ~TaskQueue();
            unsigned int Size();
            void Push(std::week_ptr<IASObject> asObject);
            std::week_ptr<IASObject> Top();
            void Pop();
            bool Empty();

        private:
            std::list<std::week_ptr<IASObject>> object_list_;
            int number_of_task_;
            TaskQueueContainer* task_queue_container_;
        };
    }
}

#endif //CORE_OBJECTCONTAINER_H
