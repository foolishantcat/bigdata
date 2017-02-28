//
// Created by Administrator on 2017/2/27 0027.
//

#ifndef CORE_THREADCONTAINER_H
#define CORE_THREADCONTAINER_H

#include <vector>
#include "CoreThread.h"
#include "CoreThreadPool.h"

namespace TBAS
{
    namespace Core
    {
        class ThreadContainer
        {
        public:
            ThreadContainer(CoreThreadPool* pPool);
            ~ThreadContainer();
            std::vector<CoreThread*>::size_type Size();
            void Assign(int number, CoreThreadPool* pPool);
            //CoreThread* Top();
            CoreThread* At(int index);
            //void Pop();
            bool IsSurvive();
            //std::mutex task_mutex_;
            std::mutex listen_mutex_;
            std::mutex notify_mutex_;
            std::condition_variable listen_cond_;
            std::condition_variable notify_cond_;

        private:
            std::vector<CoreThread*> thread_core_vector_;
            CoreThreadPool* thread_pool_;
            //not open for outside
            void Push(CoreThread* pThread);
            void Erase(CoreThread* pThread);
            typedef std::vector<CoreThread*> Container;
            typedef Container::iterator Iterator;
        };
    }
}

#endif //CORE_THREADCONTAINER_H
