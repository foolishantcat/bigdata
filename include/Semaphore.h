//
// Created by Administrator on 2017/3/1 0001.
//

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

namespace TBAS{
    namespace Core
    {
        class Semaphore
        {
        public:
            Semaphore(int value = 1): count_{value}, wakeups_{0} {}

            void Wait()
            {
                std::unique_lock<std::mutex> lock{mutex_};
                if (--count_ < 0)
                {
                    // count is not enough ?
                    condition_.wait(lock, [&]()->bool{ return wakeups_ > 0;}); // suspend and wait ...
                    --wakeups_;  // ok, me wakeup !
                }
            }
            void Signal()
            {
                std::lock_guard<std::mutex> lock{mutex_};
                if(++count_ <= 0)
                { // have some thread suspended ?
                    ++wakeups_;
                    condition_.notify_one(); // notify one !
                }
            }

        private:
            int count_;
            int wakeups_;
            std::mutex mutex_;
            std::condition_variable condition_;
        };
    }
}

#endif //SEMAPHORE_H
