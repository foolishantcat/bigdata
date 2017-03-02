//
// Created by Administrator on 2017/2/27 0027.
//

#ifndef CORELOCK_H
#define CORELOCK_H

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

#endif //CORELOCK_H
