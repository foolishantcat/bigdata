//
// Created by Administrator on 2017/2/27 0027.
//

#include <vector>
#include "CoreThreadPool.h"
#include "CoreThread.h"
#include "ThreadContainer.h"

using namespace TBAS::Core;

int ThreadContainer::number_of_thread_ = 0;

ThreadContainer::ThreadContainer(CoreThreadPool* pPool)
{
    thread_pool_ = pPool;
}

ThreadContainer::~ThreadContainer()
{
    for(Iterator it = thread_core_vector_.begin();
        it != thread_core_vector_.end();
        it++)
    {
        delete *it;
    }
}

unsigned int ThreadContainer::Size()
{
    return thread_core_vector_.size();
}

void ThreadContainer::Assign(int number, CoreThreadPool* pPool)
{
    for(int i = 0; i < number; i++)
    {
        CoreThread* thread = new CoreThread(i+1, true, pPool);
        Push(thread);
    }
}

void ThreadContainer::Push(CoreThread* pThread)
{
    thread_core_vector_.push_back(pThread);
}

void ThreadContainer::Erase(CoreThread* pThread)
{
    thread_core_vector_.erase(std::find(thread_core_vector_.begin(), thread_core_vector_.end(), pThread));
}

CoreThread* ThreadContainer::At(int index)
{
    if((unsigned int)index >= thread_core_vector_.size())
        return NULL;

    return thread_core_vector_.at(index);
}

bool ThreadContainer::IsSurvive()
{
    return thread_pool_->IsSurvive();
}


