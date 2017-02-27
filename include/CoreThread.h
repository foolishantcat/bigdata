//
// Created by Administrator on 2017/2/24 0024.
//

#ifndef TBAS_CORE_IASTHEAD_H
#define TBAS_CORE_IASTHEAD_H

#include <list>
#include <thread>
#include "IASObject.h"
#include "CoreThreadPool.h"

namespace TBAS
{
    namespace Core
    {
        class CoreThread
        {
        public:
            CoreThread();
            CoreThread(CoreThreadPool* threadPool, int threadId, bool isDetached);
            virtual ~CoreThread();
            friend bool operator==(CoreThread thd1, CoreThread thd2);
            friend bool operator!=(CoreThread thd1, CoreThread thd2);
            void AssignTask(std::week_ptr<IASObject> asObject);
            void Run();
            void StartThread();
            int GetThreadId();
            void SetIsDetach(bool idDetach);
        private:
            CoreThreadPool* thread_pool_;
            static int number_of_thread_;
            //1--task thread 2--listen thread 3-- notify thread
            int thread_id_;
            bool is_detached_;
            //Task Queue , List Complete
            std::list<std::week_ptr<IASObject>> task_list_;
            std::thread* thread_this_;
        };
    }
}

#endif //TBAS_CORE_IASTHEAD_H
