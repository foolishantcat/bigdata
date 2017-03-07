//
// Created by caoyc on 2017/2/27 0027.
//

#ifndef CORELOCK_H
#define CORELOCK_H

#include <mutex>

namespace TBAS
{
    namespace Core
    {
        class CLock
        {
        public:
            CLock(std::mutex* mMutex);
            virtual ~CLock();

        private:
            std::mutex* mutex_;
        };
    }
}

#endif //CORELOCK_H
