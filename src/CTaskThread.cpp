#include <iostream>
#include <fstream>
#include "CTaskThread.h"
#include "CScheduler.h"
#include "LuaContext.hpp"
#include "CMyTask.h"

using namespace std;
using namespace TBAS::Core;

typedef std::shared_ptr<IASObject> TASK_OBJ;
typedef std::weak_ptr<IASObject> TASK_OBJ_WK;
typedef std::mutex CMutex;

CTaskThread::CTaskThread(int nThreadID, void* lpvContext)
{
	cout << "CTaskThread::CTaskThread" << endl;
	m_lpScheduler = (CScheduler*)lpvContext;
	m_ThreadID = nThreadID;
	m_bStop = true;		//µ±Ç°Í£Ö¹
	m_TaskList.clear();
	m_NotifyList.clear();
}

CTaskThread::~CTaskThread()
{

}

bool CTaskThread::Start()
{
	cout << "CTaskThread::Start()" << endl;

	m_bStop = false;

	std::thread thread_new = std::thread(&CTaskThread::OnRun, this);

	m_Thread_ = std::move(thread_new);

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


	if (m_Thread_.joinable())
	{
		m_Thread_.join();
	}
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
			if (m_bStop && m_TaskList.empty())
			{
				if(DEBUG) cout << "CTaskThread Stop" << endl;
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
				if (DEBUG) cout << "6" << endl;
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
				if (DEBUG) cout << "7" << endl;
				std::lock_guard<std::mutex> lock(m_NotifyMutex);
				m_NotifyList.push_back(task);
			}

			if (DEBUG) cout << "8" << endl;

			//lua
			std::string modulePara = task->stringData();
			std::string commandStr = task->commandString();
			//char funcStr[512] = {0};
 			//ostr << commandStr << "(" << modulePara << ")" << endl;
			std::string execStr;
			//execStr = "return " + commandStr + "(\"" + modulePara + "\")";
			execStr = "return " + commandStr + "(inAsyncString)";
			

			if(DEBUG) cout << "funcStr : " << execStr << endl;

 			LuaContext* lua = CScheduler::luaContext();

			if (DEBUG) cout << "9" << endl;

			std::string luaRet;
			try
			{
				lua->writeVariable("inAsyncString", modulePara);
				luaRet = lua->executeCode<std::string>(execStr.c_str());
				if (DEBUG) cout << "Success : " << luaRet << endl;
			}
			catch (const exception &e) {
				printf ("load %s exception:%s\n", commandStr.c_str(), e.what());
				return;
			}

			if (DEBUG) cout << "10" << endl;

			std::shared_ptr<CMyTask> msgTask = std::make_shared<CMyTask>();
			msgTask->setCommandString(commandStr);
			msgTask->setStringData(luaRet.c_str());

			CMessageThread* msgThread = m_lpScheduler->GetMsgThread();
			msgThread->AddMessage(msgTask);

			
			if (DEBUG) cout << "11" << endl;

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
