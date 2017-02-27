//
// Created by Administrator on 2017/2/27 0027.
//

#include <vector>
#include "CoreThreadPool.h"
#include "CoreThread.h"

ThreadContainer::ThreadContainer()
{

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

std::vector<CoreThread*>::size_type ThreadContainer::Size()
{
    return thread_core_vector_.size();
}

void ThreadContainer::Assign(int number, CoreThreadPool* pPool)
{
    for(int i = 0; i < number; i++)
    {
        CoreThread* thread = new CoreThread(pPool);
        thread_core_vector_.push_back(thread);
    }
}

CoreThread* ThreadContainer::Top()
{
    return thread_core_vector_.back();
}

void ThreadContainer::Pop()
{
    thread_core_vector_.pop_back();
}

void ThreadContainer::Erase(CoreThread* pThread)
{
    thread_core_vector_.erase(std::find(thread_core_vector_.begin(), thread_core_vector_.end(), pThread));
}

CoreThread* At(int index)
{
    if(index >= thread_core_vector_.size())
        return NULL;

    return thread_core_vector_.at(index);
}


