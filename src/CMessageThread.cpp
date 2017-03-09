#include <iostream>
#include "CMessageThread.h"
#include "Global.h"
#include "CTaskThread.h"
#include "CScheduler.h"

using namespace std;
using namespace TBAS::Core;

typedef std::shared_ptr<IASObject> TASK_OBJ;
typedef std::weak_ptr<IASObject> TASK_OBJ_WK;
typedef std::mutex CMutex;

CMessageThread::CMessageThread(int nThreadID, void* lpvContext)
{
	cout << "CMessageThread::CMessageThread" << endl;
	m_lpScheduler = (CScheduler*)lpvContext;
	m_ThreadID = nThreadID;
	m_bStop = true;		//µ±Ç°Í£Ö¹
	m_MessageList.clear();
}

CMessageThread::~CMessageThread()
{

}

bool CMessageThread::OnInitThread()
{
	cout << "CMessageThread::OnInitThread()" << endl;
	m_bStop = false;

	return true;
}

bool CMessageThread::Push(TASK_OBJ asObject)
{
	m_MessageList.push_back(asObject);

	return true;
}

void CMessageThread::Stop()
{
	do
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		m_bStop = true;
		m_SemMessage.Signal();

	} while (0);

	CThread::Stop();
}

#define DEBUG 0

//excute call-back function
void CMessageThread::OnRun()
{
	if(DEBUG) cout << "CMessageThread::OnRun()  " << m_ThreadID << endl;

	CTaskThread* taskThread = m_lpScheduler->GetTaskThread();

	while (true)
	{
		std::list<std::shared_ptr<IASObject>> list_temp;
		std::shared_ptr<IASObject> task;

		if (DEBUG) cout << "1" << endl;
		do 
		{
			if (m_bStop && m_MessageList.empty())
			{
				if (DEBUG) cout << "CMessageThread Stop" << endl;
				return;
			}
			if (DEBUG) cout << "2" << endl;
			m_SemMessage.Wait();

			std::lock_guard<std::mutex> lock(m_Mutex);
			if (DEBUG) cout << "3" << endl;
			list_temp.clear();
			list_temp.swap(this->m_MessageList);

		} while (0);

		while (!list_temp.empty())
		{
			task = list_temp.front();

			if (DEBUG) cout << "4" << endl;

			std::list<TASK_OBJ_WK>& notify_list = taskThread->NotifyList();

			if (DEBUG) cout << "5" << endl;
			for (auto it = notify_list.begin();
				it != notify_list.end();
				)
			{
				auto sp_notify = it++->lock();

				if (!sp_notify)
				{
					notify_list.pop_front();
					continue;
				}

				if (DEBUG) cout << "6" << endl;

				if ((sp_notify->commandString() != task->commandString()) ||
					(sp_notify->onCommandTaskSuccess == NULL))
					continue;

				if (DEBUG) cout << "7" << endl;

				sp_notify->onCommandTaskSuccess(sp_notify);

			}

			list_temp.pop_front();
		}

		if (DEBUG) cout << "8" << endl;
	}
}

std::list<TASK_OBJ>& CMessageThread::MessageList()
{
	return m_MessageList;
}

void CMessageThread::AddMessage(TASK_OBJ asObject)
{
	do
	{
		std::lock_guard<std::mutex> Lock(m_Mutex);
		m_MessageList.push_back(asObject);

	} while (0);

	m_SemMessage.Signal();
}

CSemaphore& CMessageThread::SemMessage()
{
	return m_SemMessage;
}

CMutex& CMessageThread::MsgMutex()
{
	return m_Mutex;
}