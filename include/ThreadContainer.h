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
            ThreadContainer();
            ~ThreadContainer();
            std::vector<CoreThread*>::size_type Size();
            void Push(CoreThread* pThread);
            void Assign(int number, CoreThreadPool* pPool);
            CoreThread* Top();
            CoreThread* At(int index);
            void Pop();
            void Erase(CoreThread* pThread);

        private:
            std::vector<CoreThread*> thread_core_vector_;
            typedef std::vector<CoreThread*> Container;
            typedef Container::iterator Iterator;
        };
    }
}

#endif //CORE_THREADCONTAINER_H
