//
// Created by Administrator on 2017/2/27 0027.
//

#include <list>
#include <memory>
#include "Common.h"
#include "IASObject.h"
#include "CoreThread.h"
#include "CoreThreadPool.h"
#include "TaskQueueContainer.h"
#include "TaskQueue.h"
#include "CoreLock.h"
#include "LuaContext.hpp"

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
	pPool->thread_container_->number_of_thread_ += 1;
    thread_id_ = threadId;
    //start thread
    //is_detached_ = isDetached;

}

void CoreThread::Start()
{
    //create thread
    std::thread thread_new = std::thread(&CoreThread::Run, this);

	thread_this_ = std::move(thread_new);

}

void CoreThread::Stop()
{
	if(thread_this_.joinable())
		thread_this_.join();
}

bool CoreThread::IsSurvive()
{
    return thread_pool_->IsSurvive();
}

int CoreThread::GetThreadId()
{
	return thread_id_;
}

void CoreThread::SetIsDetach(bool isDetach)
{
	is_detached_ = isDetach;
	if(true == isDetach)
		thread_this_.detach();
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
        TaskQueueContainer* task_queue_container = thread_pool_->task_queue_container_;
        TaskQueue* queue = NULL;
        std::list<std::weak_ptr<IASObject>> wk_list_temp;
		std::list<std::shared_ptr<IASObject>> list_temp;
		wk_list_temp.clear();
		list_temp.clear();
        std::weak_ptr<IASObject> wk_task;

        if(1 == thread_id_)
        {
            queue = task_queue_container->At(0);
            CoreLock lk(&(thread_pool_->queue_task_mutex_));
			list_temp.swap(queue->object_list_);
        }
        else if(2 == thread_id_)
        {
            queue = task_queue_container->At(1);
            CoreLock lk(&(thread_pool_->queue_task_mutex_));
			wk_list_temp.swap(queue->wk_object_list_);
        }
        else
            throw thread_id_;

		//task and message queue
        while (! list_temp.empty())
        {
            wk_task = list_temp.front();

			//lock
			if (auto spt = wk_task.lock())
			{
				if (1 == thread_id_)
					HandleTask(wk_task);        //logic
				else if (2 == thread_id_)
					HandleMessage(wk_task);      //logic
				else
					throw thread_id_;
			}

            list_temp.pop_front();
        }

		//notify queue
		while (!wk_list_temp.empty())
		{
			wk_task = wk_list_temp.front();

			//lock
			if (auto spt = wk_task.lock())
			{
				if (1 == thread_id_)
					HandleTask(wk_task);        //logic
				else if (2 == thread_id_)
					HandleMessage(wk_task);      //logic
				else
					throw thread_id_;
			}

			wk_list_temp.pop_front();
		}

        //sem_wait
        {
            if(1 == thread_id_)
            {
				thread_pool_->sem_task_.Wait();
            }
            else if(2 == thread_id_)
            {
                thread_pool_->sem_message_.Wait();
            }
            else
                throw thread_id_;
        }
    }
}

void CoreThread::HandleTask(std::weak_ptr<IASObject> asObject)
{
	do 
	{
		//check weak-ptr
		CHECK_WEEK_PTR_VALID(asObject);
		std::shared_ptr<IASObject> sp = asObject.lock();

		//check if has call-back function, add to notify queue
		if (!(sp->commandString().empty()) && (NULL != sp->onCommandTaskSuccess))
		{
			CoreLock lk(&(thread_pool_->queue_notify_mutex_));
			thread_pool_->task_queue_container_->At(QUEUE_NOTIFY_ID)->Push(sp);
		}

		//check json data, ignore this

		//call module func
		std::string modulePara = sp->stringData();
		std::string commandStr = sp->commandString();
		ostringstream ostr;
		ostr << commandStr << "(" << modulePara << ")" << endl;
		LuaContext lua;
		//get return string value
		std::string luaRet = lua.executeCode<std::string >(ostr.str().c_str());
		//new IASObject , Same commandString and set return string to data
		std::shared_ptr<IASObject> msgTask = std::make_shared<IASObject>();
		msgTask->setCommandString(commandStr);
		msgTask->setStringData(luaRet.c_str());
		//throw IASObject into Message queue
		//get task queue
		TaskQueue* taskQueue = thread_pool_->task_queue_container_->At(QUEUE_MESSAGE_ID);

		{
			std::lock_guard<std::mutex> lk(thread_pool_->queue_message_mutex_);
			taskQueue->Push(asObject);
		}

		//notify
		thread_pool_->sem_message_.Signal();
		// done

	} while (0);
}

//excute call-back function
void CoreThread::HandleMessage(std::weak_ptr<IASObject> asObject)
{
	do 
	{
		//check weak-ptr
		CHECK_WEEK_PTR_VALID(asObject);
		std::shared_ptr<IASObject> sp_message = asObject.lock();
		
		//loop notify queue, and compare notify queue's command with Message queue's command line
		//std::list<std::weak_ptr<IASObject>> wp_list_temp;

		{
			CoreLock lk(&(thread_pool_->queue_notify_mutex_));

// 			wp_list_temp.assign(thread_pool_->task_queue_container_->At(QUEUE_NOTIFY_ID)->wk_object_list_.begin(),
// 				thread_pool_->task_queue_container_->At(QUEUE_NOTIFY_ID)->wk_object_list_.end());
			//thread run call-back function
			for (auto it = thread_pool_->task_queue_container_->At(QUEUE_NOTIFY_ID)->wk_object_list_.begin();
				it != thread_pool_->task_queue_container_->At(QUEUE_NOTIFY_ID)->wk_object_list_.end(); 
				it++)
			{
				auto sp_notify = it->lock();

				if (!sp_notify)
				{
					thread_pool_->task_queue_container_->At(QUEUE_NOTIFY_ID)->Pop();
					continue;
				}

				if((sp_notify->commandString() != sp_message->commandString()) ||
					(sp_notify->onCommandTaskSuccess == NULL))
					continue;

				sp_notify->onCommandTaskSuccess(sp_notify);
				
			}
			
		}

		//done

	} while (0);
}
