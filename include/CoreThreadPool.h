//
// Created by Administrator on 2017/2/24 0024.
//

#ifndef CORE_THREAD_POOL_H
#define CORE_THREAD_POOL_H

#include <list>
#include <mutex>
#include <memory>
#include <thread>
#include "IASObject.h"
#include "ThreadContainer.h"
#include "TaskQueueContainer.h"

#include "Semaphore.h"

namespace TBAS
{
    namespace Core
    {
		class Scheduler;
        class CoreThreadPool
        {
        public:
            CoreThreadPool(){};
			CoreThreadPool(int number);
            virtual ~CoreThreadPool();
            void Init();
            void AddTask(std::weak_ptr<IASObject> asObject);
            //void Start();
			void Run();
            void EndCoreThreadPool();
            bool IsSurvive();
            ThreadContainer* GetThreadContainer();
            TaskQueueContainer* GetTaskQueueContainer();

			std::mutex queue_task_mutex_;
			std::mutex queue_message_mutex_;
			std::mutex queue_notify_mutex_;

			Semaphore sem_task_;
			Semaphore sem_notify_;

        private:
            bool is_survive_;
            int number_of_thread_;
            Scheduler* scheduler_;

            ThreadContainer* thread_container_;
            TaskQueueContainer* task_queue_container_;

            std::thread thread_this_;
            std::thread thread_init_;

            std::mutex survive_mutex_;
			std::mutex task_mutex_;
        };

    }

}

#endif //TBAS_CORE_IASTHREADPOOL_H
