#pragma once
#ifndef _MESSAGE_THREAD_H_
#define _MESSAGE_THREAD_H_

#include <memory>
#include <mutex>
#include "CThread.h"
#include "CSemaphore.h"

namespace TBAS
{
	namespace Core
	{
		class CScheduler;
		class CMessageThread : public CThread
		{
		public:
			void OnRun();
			bool OnInitThread();

		public:
			CMessageThread(int nThreadID, void* lpvContext);
			~CMessageThread();

		public:
			typedef std::shared_ptr<IASObject> TASK_OBJ;
			//typedef std::weak_ptr<IASObject> TASK_OBJ_WK;
			typedef std::mutex CMutex;
			bool Push(TASK_OBJ asObject);
			void Stop();
			void AddMessage(TASK_OBJ asObject);

		public:
			std::list<TASK_OBJ>& MessageList();
			CSemaphore& SemMessage();
			CMutex& MsgMutex();

		private:
			CScheduler* m_lpScheduler;

			bool m_bStop;

			std::list<TASK_OBJ> m_MessageList;

			int m_ThreadID;

			CSemaphore m_SemMessage;

			CMutex m_Mutex;
		};
	}
}

#endif // !_MESSAGE_THREAD_H_


