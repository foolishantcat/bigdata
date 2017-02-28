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

    thread_this_ = thread_new;
}

bool CoreThread::IsSurvive()
{
    return thread_container_->IsSurvive();
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
        std::list<std::week_ptr<IASObject>> list_tmp;
        list_tmp.clear();
        std::week_ptr<IASObject> wk_task = NULL;

        while(true)
        {
            if(1 == thread_id_)
            {
                queue = task_queue_container->At(0);
                wk_task = queue->Top();
                HandleTask(wk_task);
            }
            else if(2 == thread_id_)
            {
                queue = task_queue_container->At(1);
                wk_task = queue->Top();
                HandleListen(wk_task);
            }
            //else if(3 == thread_id_)
            //{
            //    queue = task_queue_container->At(2);
            //    wk_task = queue->Top();
            //    HandleNotify(wk_task);
            //}
            else
                break;
        }

        //logic


        //sem_wait
        {
            std::unique_lock<std::mutex> lk(cv_m);
            std::cout << "Waiting... \n";
            if(1 == thread_id_)
                cv.wait(lk, []{return i == 1;});
            else if(2 == thread_id_)
                cv.wait(lk, []{return i == 1;});
            //else if(3 == thread_id_)
            //    cv.wait(lk, []{return i == 1;});
            else
                break;
        }
    }
}

void CoreThread::HandleTask(std::week_ptr<IASObject> asObject)
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
void CoreThread::HandleNotify(std::week_ptr<IASObject> asObject)
{
    //pop Message queue

    //campare notify queue's command with Message queue's command line

    //thread run call-back function

    //done

}
