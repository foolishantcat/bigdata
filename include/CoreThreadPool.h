//
// Created by Administrator on 2017/2/24 0024.
//

#ifndef TBAS_CORE_IASTHREADPOOL_H
#define TBAS_CORE_IASTHREADPOOL_H

#include <list>
#include <mutex>
#include <memory>
#include <thread>
#include "IASObject.h"
#include "ThreadContainer.h"

using namespace std;

class Scheduler;
namespace TBAS
{
    namespace Core
    {
        class CoreThreadPool
        {
        public:
            CoreThreadPool(){};
            CoreThreadPool(int number = 2, Scheduler* scheduler);
            virtual ~CoreThreadPool();
            void Init();
            void AddTask(std::week_ptr<IASObject> asObject);
            void Start();
            void EndCoreThreadPool();
            bool IsSurvive();
            ThreadContainer* GetThreadContainer();
            TaskQueueContainer* GetTaskQueueContainer();

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
            std::condition_variable task_cond_;
        };

    }

}

#endif //TBAS_CORE_IASTHREADPOOL_H
