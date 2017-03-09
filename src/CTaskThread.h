#pragma once
#ifndef _TASK_THREAD_H_
#define _TASK_THREAD_H_

#include <mutex>
#include <memory>
#include <list>
#include "Global.h"
#include "CThread.h"
#include "CSemaphore.h"

namespace TBAS
{
	namespace Core
	{
		class CScheduler;
		class CTaskThread
		{
		public :
			void OnRun();
			bool Start();
			void Stop();

		public:
			CTaskThread(int nThreadID, void* lpvContext);
			~CTaskThread();

		public:
			typedef std::shared_ptr<IASObject> TASK_OBJ;
			typedef std::weak_ptr<IASObject> TASK_OBJ_WK;
			typedef std::mutex CMutex;
			bool Push(TASK_OBJ_WK asObject);
			bool Push(TASK_OBJ asObject);


		public:
			std::list<TASK_OBJ>& TaskList();
			std::list<TASK_OBJ_WK>& NotifyList();
			CMutex& TaskMutex();
			CMutex& NotifyMutex();
			CSemaphore& SemTask();

		private:
			CScheduler* m_lpScheduler;

			bool m_bStop;

			std::list<TASK_OBJ> m_TaskList;
			std::list<TASK_OBJ_WK> m_NotifyList;

			int m_ThreadID;
			std::thread m_Thread_;

			CSemaphore m_SemTask;

			CMutex m_TaskMutex;
			CMutex m_NotifyMutex;

			CMutex m_Mutex;
		};
	}
}


#endif //_TASK_THREAD_H_