//
// Created by caoyc on 2017/2/27 0027.
//

//#include <iostream>
#include <mutex>
#include "CLock.h"

using namespace TBAS::Core;

CLock::CLock(std::mutex* mMutex)
{
    mutex_ = mMutex;
    mutex_->lock();
}

CLock::~CLock()
{
    mutex_->unlock();
}
