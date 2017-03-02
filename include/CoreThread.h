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
            CoreThread(int threadId, bool isDetached = false, CoreThreadPool* pPool = NULL);
            virtual ~CoreThread();
            //friend bool operator==(CoreThread thd1, CoreThread thd2);
            //friend bool operator!=(CoreThread thd1, CoreThread thd2);
            //void AssignTask(std::week_ptr<IASObject> asObject);
            void Start();     //create and start thread
			void Stop();
            int GetThreadId();
            void SetIsDetach(bool isDetach);
            bool IsSurvive();

        private:
            CoreThreadPool* thread_pool_;
            void Run();             //thread's handler
            void HandleTask(std::weak_ptr<IASObject> asObject);
            void HandleMessage(std::weak_ptr<IASObject> asObject);
			void CallLuaFunction();
            static int number_of_thread_;
            //1--task thread 2--listen thread 3-- notify thread
            int thread_id_;
            bool is_detached_;
            std::thread thread_this_;
        };
    }
}

#endif //CORE_THEAD_H
