//
// Created by Administrator on 2017/2/27 0027.
//

#include <mutex>
#include "CoreLock.h"

using namespace TBAS::Core;

CoreLock::CoreLock(std::mutex* mMutex)
{
    mutex_ = mMutex;
    mutex_->lock();
}

CoreLock::~CoreLock()
{
    mutex_->unlock();
}
