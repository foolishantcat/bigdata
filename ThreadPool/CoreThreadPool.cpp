//
// Created by Administrator on 2017/2/27 0027.
//
#include <iostream>
#include <thread>
#include "Common.h"
#include "CoreLock.h"
#include "IASObject.h"
#include "Scheduler.h"
#include "TaskQueueContainer.h"
#include "ThreadContainer.h"
#include "CoreThreadPool.h"

using namespace std;
using namespace TBAS::Core;

CoreThreadPool::~CoreThreadPool()
{
    if(NULL != thread_container_)
        delete thread_container_;
    if(NULL != task_queue_container_)
        delete task_queue_container_;
}

CoreThreadPool::CoreThreadPool(int number, Scheduler* pScheduler)
{
    is_survive_ = true;
    number_of_thread_ = number;
}

void CoreThreadPool::AddTask(std::weak_ptr<IASObject> asObject)
{
    do
    {
		//cout << "before add task : " << is_survive_ << " | " << endl;
        CHECK_POOL_SURVIVE(is_survive_);
		//cout << "000" << endl;
        CHECK_WEEK_PTR_VALID(asObject);
		//cout << "123" << endl;
        //get task queue
        TaskQueue* taskQueue = task_queue_container_->At(0);
		//cout << "456" << endl;
        {
			//cout << "lock_guard" << endl;
            std::lock_guard<std::mutex> lk(/*task_mutex_*/queue_task_mutex_);
            taskQueue->Push(asObject);
			//cout << "after push" << endl;
        }

        //notify
		sem_task_.Signal();
		//cout << "after signal " << endl;

    }while(0);

}

void CoreThreadPool::Init()
{
    do
    {
        //if(true != is_survive_)
            //break;
        CHECK_POOL_SURVIVE(is_survive_);

		//Create thread for pop task queue.
		//thread_init_ = std::move(std::thread(&CoreThreadPool::Init, this));
		//thread_this_.detach();

        task_queue_container_ = new TaskQueueContainer(this);
        thread_container_ = new ThreadContainer(this);

        //create queue
        task_queue_container_->Assign(NUMBER_OF_TASK_QUEUE, task_queue_container_);

        //create thread for task / listen / notify
        thread_container_->Assign(NUMBER_OF_THREAD, this);

    } while (0);
}

void CoreThreadPool::Run()
{
    //create and run thread container's three thread
    for(int i = 0; i < number_of_thread_; i++)
    {
        CoreThread* thread = thread_container_->At(i);
        //create and start thread
        thread->Start();
    }
}

void CoreThreadPool::EndCoreThreadPool()
{
    //lock
    CoreLock lock(&survive_mutex_);

    is_survive_ = false;
	cout << "is_survive = false " << endl;
    //join thread
    for (int i = 0; i < thread_container_->number_of_thread_; i++)
    {
		thread_container_->At(i)->Stop();
    }
}

bool CoreThreadPool::IsSurvive()
{
	return is_survive_;
}

