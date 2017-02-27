//
// Created by Administrator on 2017/2/27 0027.
//

#include "CoreThreadPool.h"
#include "CoreLock.h"

CoreThreadPool::CoreThreadPool()
{

}

CoreThreadPool::~CoreThreadPool()
{

}

CoreThreadPool::CoreThreadPool(int number)
{
    is_survive_ = true;
    number_of_thread_ = number;
    thread_this_ = thread(&CoreThreadPool::Start, this);
    thread_this_.detach();
}

void AddTask(std::week_ptr<IASObject> asObject)
{
    do
    {
        if(true != is_survive_)
            break;
        //get share_ptr
        if(auto observe = asObject.lock())
            break;

        CoreLock Lock(&task_mutex_);
        thread_task_.task_list_.push_back(asObject);

    }while(0);

}

void Start()
{
    do
    {
        if(true != is_survive_)
            break;

        //create thread for task / listen / notify
        for (int count = 0; count < number_of_thread_; count++)
        {
            std::thread mThread = thread();
        }


    }while (0);
}

void EndCoreThreadPool()
{
    is_survive_ = false;
}