//
// Created by caoyc on 2017/2/27 0027.
//
#include <iostream>
#include <thread>
#include "Global.h"
#include "CLock.h"
#include "CScheduler.h"
#include "CMessageThread.h"
#include "CTaskThread.h"
#include "CThreadPool.h"

using namespace std;
using namespace TBAS::Core;

typedef std::shared_ptr<IASObject> TASK_OBJ;
typedef std::weak_ptr<IASObject> TASK_OBJ_WK;
typedef std::mutex CMutex;

CThreadPool::CThreadPool()
{
	cout << "CThreadPool::CThreadPool" << endl;
	m_bSurvive = true;
	m_ThreadNums = -1;
}

CThreadPool::~CThreadPool()
{

}

CThreadPool* CThreadPool::CreateThreadPool(int number, CScheduler* pScheduler)
{
	CThreadPool* lpThreadPool = NULL;

	lpThreadPool = new CThreadPool;
	lpThreadPool->m_ThreadNums = number;

	lpThreadPool->m_ThreadTask = new CTaskThread(THREAD_TASK_ID, (void*)lpThreadPool);
	lpThreadPool->m_ThreadTask->Start();

	lpThreadPool->m_ThreadMessage = new CMessageThread(THREAD_MESSAGE_ID, (void*)lpThreadPool);
	lpThreadPool->m_ThreadMessage->Start();

	return lpThreadPool;
}

void CThreadPool::Release()
{
	m_ThreadTask->Stop();
	m_ThreadMessage->Stop();

	delete this;
}

void CThreadPool::AddTask(TASK_OBJ asObject)
{
	CTaskThread* taskThread = GetTaskThread();

    do
    {
        CHECK_POOL_SURVIVE(m_bSurvive);

		std::lock_guard<std::mutex> lock(taskThread->TaskMutex());

		taskThread->TaskList().push_back(asObject);

		taskThread->SemTask().Signal();

    }while(0);

}

void CThreadPool::AddNotify(TASK_OBJ_WK asObject)
{
	CTaskThread* taskThread = GetTaskThread();

	do
	{
		CHECK_POOL_SURVIVE(m_bSurvive);

		std::lock_guard<std::mutex> lock(taskThread->NotifyMutex());
		taskThread->NotifyList().push_back(asObject);

	} while (0);
}

void CThreadPool::Clear()
{

}

CTaskThread* CThreadPool::GetTaskThread()
{
	cout << "CThreadPool::GetTaskThread()" << endl;
	return m_ThreadTask;
}

CMessageThread* CThreadPool::GetMsgThread()
{
	return m_ThreadMessage;
}



