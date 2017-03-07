#include <iostream>
#include <fstream>
#include "CTaskThread.h"
#include "CThreadPool.h"
#include "CLock.h"
#include "LuaContext.hpp"
#include "CMyTask.h"
#include "CLock.h"
#include "CScheduler.h"

using namespace std;
using namespace TBAS::Core;

typedef std::shared_ptr<IASObject> TASK_OBJ;
typedef std::weak_ptr<IASObject> TASK_OBJ_WK;
typedef std::mutex CMutex;

CTaskThread::CTaskThread(int nThreadID, void* lpvContext)
{
	cout << "CTaskThread::CTaskThread" << endl;
	m_lpThreadPool = (CThreadPool*)lpvContext;
	m_ThreadID = nThreadID;
	m_bStop = true;		//µ±Ç°Í£Ö¹
	m_TaskList.clear();
	m_NotifyList.clear();
}

CTaskThread::~CTaskThread()
{

}

bool CTaskThread::OnInitThread()
{
	cout << "CTaskThread::OnInitThread()" << endl;
	m_bStop = false;

	return true;
}

void CTaskThread::Stop()
{
	do 
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		m_bStop = true;
		m_SemTask.Signal();

	} while (0);

	CThread::Stop();
}

bool CTaskThread::Push(TASK_OBJ asObject)
{
	m_TaskList.push_back(asObject);
	
	return true;
}

bool CTaskThread::Push(TASK_OBJ_WK asObject)
{
	m_NotifyList.push_back(asObject);
	
	return true;
}

#define DEBUG 0

void CTaskThread::OnRun()
{
	if (DEBUG) cout << "CTaskThread::OnRun()" << endl;

	while (true)
	{
		if (DEBUG) cout << "1" << endl;
		std::list<std::shared_ptr<IASObject>> list_temp;
		std::shared_ptr<IASObject> task;
		list_temp.clear();
		do
		{
			if (m_bStop)
			{
				return;
			}
			if (DEBUG) cout << "2" << endl;
			m_SemTask.Wait();
			if (DEBUG) cout << "3" << endl;

			std::lock_guard<std::mutex> lock(m_TaskMutex);

			list_temp.swap(m_TaskList);

		} while (0);

		if (DEBUG) cout << "4" << endl;

		while (!list_temp.empty())
		{
			task = list_temp.front();

			if (DEBUG) cout << "5" << endl;
			//delete if need
			if (!(task->commandString().compare("DELETE_NOTIFY")) && !(task->stringData().empty()))
			{
				std::lock_guard<std::mutex> lock(m_NotifyMutex);

				for (auto it = m_NotifyList.begin();
					it != m_NotifyList.end();
					)
				{
					auto it_temp = it++;
					if (auto sp_notify = it->lock())
					{
						if (task->stringData().compare(sp_notify->commandString()))
							m_NotifyList.erase(it_temp);
					}
					else
					{
						m_NotifyList.erase(it_temp);
					}
				}

				break;
			}

			//add task to notify queue
			if (!(task->commandString().empty()) && (NULL != task->onCommandTaskSuccess))
			{
				std::lock_guard<std::mutex> lock(m_NotifyMutex);
				m_NotifyList.push_back(task);
			}

			//lua
			std::string modulePara = task->stringData();
			std::string commandStr = task->commandString();
// 			ostringstream ostr;
// 			ostr << commandStr << "(" << modulePara << ")" << endl;
			LuaContext* lua = CScheduler::luaContext();
			std::ifstream ifs("./option_service.lua");
			ifs.close();

			Config* luaConfig = Config::instance();
			std::string func;
			if (luaConfig->findFunction(commandStr, func))
			{
				cout << "Success: " << func << endl;
			}
			else
			{

			}

 			const auto function = lua->readVariable<std::function<std::string(std::string)>>("execute");
 			std::string luaRet = function(func);

			std::shared_ptr<CMyTask> msgTask = std::make_shared<CMyTask>();
			msgTask->setCommandString(commandStr);
			msgTask->setStringData(luaRet.c_str());

			CMessageThread* msgThread = m_lpThreadPool->GetMsgThread();
			msgThread->AddMessage(msgTask);


			list_temp.pop_front();
		}
	}
}

std::list<TASK_OBJ>& CTaskThread::TaskList()
{
	return m_TaskList;
}

std::list<TASK_OBJ_WK>& CTaskThread::NotifyList()
{
	return m_NotifyList;
}

CMutex& CTaskThread::TaskMutex()
{
	return m_TaskMutex;
}

CMutex& CTaskThread::NotifyMutex()
{
	return m_NotifyMutex;
}

CSemaphore& CTaskThread::SemTask()
{
	return m_SemTask;
}
