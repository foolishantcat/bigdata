//
// Created by Administrator on 2017/2/27 0027.
//

#include "CoreThread.h"
#include "CoreThreadPool.h"

int CoreThread::number_of_thread_ = 0;

CoreThread::CoreThread()
{

}

CoreThread::~CoreThread()
{

}

CoreThread::CoreThread(CoreThreadPool* threadPool, int threadId, bool isDetached)
{
    thread_pool_ = threadPool;
    number_of_thread_ += 1;
    thread_id_ = threadId;
    //start thread
    is_detached_ = isDetached;
    th
}
