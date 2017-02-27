//
// Created by Administrator on 2017/2/27 0027.
//

#ifndef CORE_CORELOCK_H
#define CORE_CORELOCK_H

#include <mutex>

namespace TBAS
{
    namespace Core
    {
        class CoreLock
        {
        public:
            CoreLock(std::mutex* mMutex);
            virtual ~CoreLock();

        private:
            std::mutex* mutex_;
        };
    }
}

#endif //CORE_CORELOCK_H
