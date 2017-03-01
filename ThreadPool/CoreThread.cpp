//
// Created by Administrator on 2017/2/27 0027.
//

#include <list>
#include <memory>
#include "IASObject.h"
#include "CoreThread.h"
#include "CoreThreadPool.h"
#include "TaskQueueContainer.h"
#include "TaskQueue.h"
#include "CoreLock.h"

using namespace std;
using namespace TBAS::Core;

int CoreThread::number_of_thread_ = 0;

CoreThread::CoreThread()
{

}

CoreThread::~CoreThread()
{

}

CoreThread::CoreThread(int threadId, bool isDetached, CoreThreadPool* pPool)
{
    thread_pool_ = pPool;
    number_of_thread_ += 1;
    thread_id_ = threadId;
    //start thread
    is_detached_ = isDetached;

}

void CoreThread::StartThread()
{
    //create thread
    std::thread thread_new = std::thread(&CoreThread::Run, this);
    //if(true == is_detached_)
    //    thread_new.detach();
    //else
    //    thread_new.join();

    //thread_this_.swap(thread_new);
	thread_this_ = std::move(thread_new);

}

bool CoreThread::IsSurvive()
{
    return thread_pool_->IsSurvive();
}

int CoreThread::GetThreadId()
{
	return 0;
}

void CoreThread::SetIsDetach(bool idDetach)
{

}

//handle logic
void CoreThread::Run()
{
    //check queue null
    while(true)
    {
        if(!IsSurvive())
            break;

        //task queue not null
        if(NULL != thread_pool_)
            break;
        //get task, and judge type
        TaskQueueContainer* task_queue_container = thread_pool_->GetTaskQueueContainer();
        TaskQueue* queue = NULL;
        std::list<std::weak_ptr<IASObject>> list_tmp;
        list_tmp.clear();
        std::weak_ptr<IASObject> wk_task;

        if(1 == thread_id_)
        {
            queue = task_queue_container->At(0);
            CoreLock lk(&(thread_pool_->queue_task_mutex_));
            list_tmp.swap(queue->object_list_);
        }
        else if(2 == thread_id_)
        {
            queue = task_queue_container->At(1);
            CoreLock lk(&(thread_pool_->queue_task_mutex_));
            list_tmp.swap(queue->object_list_);
        }
        else
            break;

        while (! list_tmp.empty())
        {
            wk_task = list_tmp.front();

            if(1 == thread_id_)
                HandleTask(wk_task);        //logic
            else if(2 == thread_id_)
                HandleMessage(wk_task);      //logic
            else
                break;

            list_tmp.pop_front();
        }

        //sem_wait
        {
            if(1 == thread_id_)
            {
				thread_pool_->sem_task_.Wait();
            }
            else if(2 == thread_id_)
            {
                thread_pool_->sem_notify_.Wait();
            }
            else
                break;
        }
    }
}

void CoreThread::HandleTask(std::weak_ptr<IASObject> asObject)
{
    //call lua

    //get return string value

    //new IASObject , Same commandString and set return string to data

    //throw IASObject into Message queue

    // done

}

//void CoreThread::HandleListen(std::week_ptr<IASObject> asObject)
//{

//}

//excute call-back function
void CoreThread::HandleMessage(std::weak_ptr<IASObject> asObject)
{
    //pop Message queue

    //campare notify queue's command with Message queue's command line

    //thread run call-back function

    //done

}
