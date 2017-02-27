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

#define NUMBER_OF_THREAD 3;

namespace TBAS
{
    namespace Core
    {
        class CoreThreadPool
        {
        public:
            CoreThreadPool(){};
            CoreThreadPool(int number = 3);
            virtual ~CoreThreadPool();
            void AddTask(std::week_ptr<IASObject> asObject);
            void Start();
            void EndCoreThreadPool();

        private:
            bool is_survive_;
            int number_of_thread_;
            ThreadContainer thread_container_;
            std::thread thread_this_;

            std::mutex task_mutex_;
            std::mutex listen_mutex_;
            std::mutex notify_mutex_;
        };

    }

}

#endif //TBAS_CORE_IASTHREADPOOL_H
