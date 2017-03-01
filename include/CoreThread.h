//
// Created by Administrator on 2017/2/24 0024.
//

#ifndef CORE_THEAD_H
#define CORE_THEAD_H

#include <list>
#include <thread>
#include "IASObject.h"

namespace TBAS
{
    namespace Core
    {
		class CoreThreadPool;
        class CoreThread
        {
        public:
            CoreThread();
            CoreThread(int threadId, bool isDetached, TBAS::Core::CoreThreadPool* pPool);
            virtual ~CoreThread();
            //friend bool operator==(CoreThread thd1, CoreThread thd2);
            //friend bool operator!=(CoreThread thd1, CoreThread thd2);
            //void AssignTask(std::week_ptr<IASObject> asObject);
            void StartThread();     //create and start thread
            int GetThreadId();
            void SetIsDetach(bool idDetach);
            bool IsSurvive();
			void HandleTask(std::weak_ptr<IASObject> asObject);
			void HandleMessage(std::weak_ptr<IASObject> asObject);

        private:
            CoreThreadPool* thread_pool_;
            void Run();             //thread's handler
            static int number_of_thread_;
            //1--task thread 2--listen thread 3-- notify thread
            int thread_id_;
            bool is_detached_;
            std::thread thread_this_;
        };
    }
}

#endif //TBAS_CORE_IASTHEAD_H
