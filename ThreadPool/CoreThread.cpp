//
// Created by Administrator on 2017/2/27 0027.
//

#include <list>
#include <memory>
#include <fstream>
#include "Common.h"
#include "IASObject.h"
#include "CoreThread.h"
#include "CoreThreadPool.h"
#include "TaskQueueContainer.h"
#include "TaskQueue.h"
#include "CoreLock.h"
#include "MyTask.h"
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
	//cout << "thread_new |:" << thread_new.get_id() << endl;
	thread_this_ = std::move(thread_new);
	//cout << "thread_this " << thread_this_.get_id() << endl;
	//cout << "thread_new 2 : " << thread_new.get_id() << endl;

}

void CoreThread::Stop()
{
	if (thread_this_.joinable())
	{
		cout << "before join ::[ " << thread_this_.get_id() << "] | " << thread_id_ << endl;
		//std::this_thread::sleep_for(std::chrono::seconds(1));
		thread_this_.join();
		cout << "after join ::[ " << thread_id_ << "]" << endl;
	}
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

#define FUCK 2

//handle logic
void CoreThread::Run()
{
	if(thread_id_ == FUCK) cout << "1--[" << thread_this_.get_id() << "]\n\n";

    //check queue null
    while(true)
    {
		{
			//确保让获取队列的操作执行完毕
			CoreLock mutex_lk(&(thread_pool_->survive_mutex_));

			if (thread_id_ == FUCK) cout << "2--!issurvive[" << !IsSurvive() << "]\n";

			if (!IsSurvive())
				break;
		}

		//sem_wait
		{
			if (THREAD_TASK_ID == thread_id_)
			{
				thread_pool_->sem_task_.Wait();
				//cout << "11--[" << thread_this_.get_id() << "]\n";
			}
			else if (THREAD_MESSAGE_ID == thread_id_)
			{
				if (thread_id_ == FUCK) cout << "3--[" << thread_this_.get_id() << "]\n";
				thread_pool_->sem_message_.Wait();
			}
			else
				throw thread_id_;
		}

		{
			if (thread_id_ == FUCK) cout << "4--[" << thread_this_.get_id() << "]\n";
			//task queue not null
			if (NULL == thread_pool_)
				break;
			//get task, and judge type
			TaskQueueContainer* task_queue_container = thread_pool_->task_queue_container_;
			TaskQueue* queue = NULL;
			//std::list<std::weak_ptr<IASObject>> wk_list_temp;
			std::list<std::shared_ptr<IASObject>> list_temp;
			//wk_list_temp.clear();
			list_temp.clear();
			std::shared_ptr<IASObject> task;
			if (thread_id_ == FUCK) cout << "5--[" << thread_this_.get_id() << "]\n";
			if (THREAD_TASK_ID == thread_id_)
			{
				queue = task_queue_container->At(QUEUE_TASK_ID);
				//cout << "5--[" << thread_this_.get_id() << "]\n";
				CoreLock lk(&(thread_pool_->queue_task_mutex_));
				list_temp.swap(queue->object_list_);
			}
			else if (THREAD_MESSAGE_ID == thread_id_)
			{
				queue = task_queue_container->At(QUEUE_MESSAGE_ID);
				//if (thread_id_ == 1) cout << "6--[" << thread_this_.get_id() << "]\n";
				CoreLock lk(&(thread_pool_->queue_message_mutex_));
				list_temp.swap(queue->object_list_);
			}
			else
			{
				//if (thread_id_ == 0) cout << "fuck\n";
				throw thread_id_;
			}

			if (thread_id_ == FUCK) cout << "6--[" << thread_this_.get_id() << "]\n";

			//task and message queue
			while (!list_temp.empty())
			{
				if (thread_id_ == FUCK) cout << "7--[" << thread_this_.get_id() << "]\n";
				task = list_temp.front();

	
				if (THREAD_TASK_ID == thread_id_)
				//{
					//cout << "comm---: " << spt->stringData()  << "||| " << spt->commandString() << endl;
					HandleTask(task);        //logic
				//}
					//HandleTask(wk_task);        //logic
				else if (THREAD_MESSAGE_ID == thread_id_)
					HandleMessage(task);      //logic
				else
					throw thread_id_;
				

				list_temp.pop_front();
			}

			if (thread_id_ == FUCK) cout << "8--[" << thread_this_.get_id() << "]\n";

			//message queue
// 			while (!wk_list_temp.empty())
// 			{
// 				if (thread_id_ == FUCK) cout << "9--[" << thread_this_.get_id() << "]\n";
// 				wk_task = wk_list_temp.front();
// 
// 				//lock
// 				if (auto spt = wk_task.lock())
// 				{
// 					if (1 == thread_id_)
// 						HandleTask(wk_task);        //logic
// 					else if (2 == thread_id_)
// 					{
// 						if (thread_id_ == FUCK) cout << "10--[" << thread_this_.get_id() << "]\n";
// 						HandleMessage(wk_task);      //logic
// 					}
// 					else
// 						throw thread_id_;
// 				}
// 
// 				wk_list_temp.pop_front();
// 			}

			//if (thread_id_ == FUCK) cout << "11--[" << thread_this_.get_id() << "]\n";
		}

    }
}

void CoreThread::HandleTask(std::shared_ptr<IASObject> asObject)
{
	do 
	{
		//check weak-ptr
		//CHECK_WEEK_PTR_VALID(asObject);
		//std::shared_ptr<IASObject> sp = asObject.lock();

		if (thread_id_ == FUCK) cout << "---stringdata--[" << !(asObject->stringData().empty()) << "]  " 
			<< asObject->commandString().compare("DELETE_NOTIFY") << endl;

		//check if delete notify,Command is self-defined
		if (!(asObject->commandString().compare("DELETE_NOTIFY")) && !(asObject->stringData().empty()))
		{
			CoreLock lk(&(thread_pool_->queue_notify_mutex_));

			//loop notify queue
			for (auto it = thread_pool_->task_queue_container_->At(QUEUE_NOTIFY_ID)->wk_object_list_.begin();
				it != thread_pool_->task_queue_container_->At(QUEUE_NOTIFY_ID)->wk_object_list_.end();
				)
			{
				auto it_temp = it++;
				if (auto sp_notify = it->lock())
				{
					if (asObject->stringData().compare(sp_notify->commandString()))
						thread_pool_->task_queue_container_->At(QUEUE_NOTIFY_ID)->Erase(it_temp);
				}
				else
				{
					//if weak_ptr invalid , delete it
					thread_pool_->task_queue_container_->At(QUEUE_NOTIFY_ID)->Erase(it_temp);
				}
			}

			break;
		}

		if (thread_id_ == FUCK) cout << "13--[" << thread_this_.get_id() << "]\n";

		//check if has call-back function, add to notify queue
		std::weak_ptr<IASObject> wk_notify_task = asObject;
		if (!(asObject->commandString().empty()) && (NULL != asObject->onCommandTaskSuccess))
		{
			CoreLock lk(&(thread_pool_->queue_notify_mutex_));
			thread_pool_->task_queue_container_->At(QUEUE_NOTIFY_ID)->Push(wk_notify_task);
		}

		if (thread_id_ == FUCK) cout << "14--[" << thread_this_.get_id() << "]\n";

		//check json data, ignore this

		//call module func
		std::string modulePara = asObject->stringData();
		std::string commandStr = asObject->commandString();
		ostringstream ostr;
		ostr << commandStr << "(" << modulePara << ")" << endl;
		LuaContext lua;
		std::ifstream ifs("./config.lua");
		lua.executeCode(ifs);
		ifs.close();
		//get return string value
		//if (thread_id_ == 1) cout << "15--[" << ostr.str().c_str() << "]\n";

		//lua.executeCode("foo = function(str) return str  end");


 		const auto function = lua.readVariable<std::function<std::string (std::string)>>("test");
		std::string luaRet = function(ostr.str());


		//if (thread_id_ == 1) cout << "16--[" << luaRet << "]\n";
		//new IASObject , Same commandString and set return string to data
		//decltype(asObject) msgTask = decltype(asObject)();
		std::shared_ptr<MyTask> msgTask = std::make_shared<MyTask>();
		msgTask->setCommandString(commandStr);
		msgTask->setStringData(luaRet.c_str());
		//throw New IASObject into Message queue
		//get task queue
		TaskQueue* taskQueue = thread_pool_->task_queue_container_->At(QUEUE_MESSAGE_ID);

		{
			std::lock_guard<std::mutex> lk(thread_pool_->queue_message_mutex_);
			taskQueue->Push(msgTask);
		}

		//notify
		thread_pool_->sem_message_.Signal();
		// done
		if (thread_id_ == FUCK) cout << "16--[" << thread_this_.get_id() << "]\n";

	} while (0);
}

//excute call-back function
void CoreThread::HandleMessage(std::shared_ptr<IASObject> asObject)
{
	do 
	{
		if (thread_id_ == FUCK) cout << "9--[" << thread_this_.get_id() << "]\n";

		CoreLock lk(&(thread_pool_->queue_notify_mutex_));

		//thread run call-back function
		for (auto it = thread_pool_->task_queue_container_->At(QUEUE_NOTIFY_ID)->wk_object_list_.begin();
			it != thread_pool_->task_queue_container_->At(QUEUE_NOTIFY_ID)->wk_object_list_.end(); 
			)
		{
			if (thread_id_ == FUCK) cout << "10--[" << thread_this_.get_id() << "]\n";
			auto sp_notify = it++ ->lock();

			if (!sp_notify)
			{
				thread_pool_->task_queue_container_->At(QUEUE_NOTIFY_ID)->Pop();
				continue;
			}

			if (thread_id_ == FUCK) cout << "11--[" << thread_this_.get_id() << "]\n";

			cout << "string:: " << sp_notify->commandString() << "| " << asObject->commandString() << endl;

			if((sp_notify->commandString() != asObject->commandString()) ||
				(sp_notify->onCommandTaskSuccess == NULL))
				continue;

			if (thread_id_ == FUCK) cout << "13--[" << thread_this_.get_id() << "]\n";

			sp_notify->onCommandTaskSuccess(sp_notify);
				
		}
			
		//done
		if (thread_id_ == FUCK) cout << "14--[" << thread_this_.get_id() << "]\n";

	} while (0);
}
