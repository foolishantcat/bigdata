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
			friend class TaskQueueContainer;
			friend class CoreThread;
        public:
            TaskQueue(TaskQueueContainer* container);
            ~TaskQueue();
            unsigned int Size();
            void Push(std::weak_ptr<IASObject> asObject);
            std::weak_ptr<IASObject> Top();
            void Pop();
            bool Empty();
			void Erase(std::list<std::weak_ptr<IASObject>>::iterator it);

        private:
            int number_of_task_;
            TaskQueueContainer* task_queue_container_;
			std::list<std::shared_ptr<IASObject>> object_list_;
			std::list<std::weak_ptr<IASObject>> wk_object_list_;		//for notify queue
			bool is_weak_ptr_;
        };
    }
}

#endif //TASK_QUQUE_H
