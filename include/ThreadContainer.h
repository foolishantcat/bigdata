//
// Created by Administrator on 2017/2/27 0027.
//

#ifndef THREADCONTAINER_H
#define THREADCONTAINER_H

#include <vector>
#include "CoreThread.h"

namespace TBAS
{
    namespace Core
    {
		class CoreThreadPool;
        class ThreadContainer
        {
        public:
            ThreadContainer(CoreThreadPool* pPool);
            ~ThreadContainer();
            unsigned int Size();
            void Assign(int number, CoreThreadPool* pPool);
            //CoreThread* Top();
            CoreThread* At(int index);
            //void Pop();
            bool IsSurvive();

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
