//
// Created by caoyc on 2017/3/1 0001.
//

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

namespace TBAS{
    namespace Core
    {
        class CSemaphore
        {
        public:
            CSemaphore(){}

            void Wait()
            {
                std::unique_lock<std::mutex> lock{mutex_};
                condition_.wait(lock);
            }
            void Signal()
            {
                std::lock_guard<std::mutex> lock{mutex_};
                condition_.notify_one(); // notify one !
            }

        private:
            std::mutex mutex_;
            std::condition_variable condition_;
        };
    }
}

#endif //SEMAPHORE_H
