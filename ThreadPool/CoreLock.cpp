//
// Created by Administrator on 2017/2/27 0027.
//

//#include <iostream>
#include <mutex>
#include "CoreLock.h"

//using namespace std;
using namespace TBAS::Core;

CoreLock::CoreLock(std::mutex* mMutex)
{
    mutex_ = mMutex;
    mutex_->lock();
}

CoreLock::~CoreLock()
{
    mutex_->unlock();
	//cout << "CoreLock::~CoreLock()" << endl;
}
