//
// Created by caoyc on 2017/2/24 0024.
//
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "CScheduler.h"
#include "Global.h"
#include "LuaContext.hpp"
#include "CMyTask.h"
#include "CTaskThread.h"
#include "CMessageThread.h"

using namespace std;
using namespace TBAS::Core;
using namespace TBAS;

#define DEBUG 0

CScheduler::CScheduler() 
{
	if(DEBUG) cout << "Get scheduler instance..." << endl;
}
CScheduler::~CScheduler() 
{
	//threadPool->EndCoreThreadPool();
	if(DEBUG) cout << "~Scheduler\n";
}

bool CScheduler::release()
{
	if(DEBUG) cout << "before CScheduler::release()" << endl;
	m_ThreadTask->Stop();
	m_ThreadMessage->Stop();

	if (NULL != m_ThreadTask)
	{
		delete m_ThreadTask;
		m_ThreadTask = NULL;
	}
	if (NULL != m_ThreadMessage)
	{
		delete m_ThreadMessage;
		m_ThreadMessage = NULL;
	}

	delete m_LuaContext;
	m_LuaContext = NULL;

	delete schedulerShared;

	schedulerShared = NULL;

	if(DEBUG) cout << "after CScheduler::release()" << endl;

	return true;
}

//For instance and de-construction
CScheduler *CScheduler::schedulerShared = NULL;
CScheduler::SchedulerGarbo CScheduler::Garbo;
const char* CScheduler::versionInfo = NULL;
Config* CScheduler::m_Config = NULL;
LuaContext* CScheduler::m_LuaContext = NULL;

//instance core frame
CScheduler* CScheduler::instance()
{
    do
	{
        //get version info

        //instance Core
        if(NULL != schedulerShared)
            break;
        else
            schedulerShared = new CScheduler();

		schedulerShared->m_bSurvive = true;
        //create and run thread
		schedulerShared->m_ThreadTask = new CTaskThread(THREAD_TASK_ID, (void*)schedulerShared);
		schedulerShared->m_ThreadTask->Start();

		schedulerShared->m_ThreadMessage = new CMessageThread(THREAD_MESSAGE_ID, (void*)schedulerShared);
		schedulerShared->m_ThreadMessage->Start();

		CScheduler::m_Config = Config::instance();

		CScheduler::m_LuaContext = new LuaContext;

    } while (0);

    return schedulerShared;
}

//get version
const char* CScheduler::version()
{
    //get version info

    return versionInfo;
}

LuaContext* CScheduler::luaContext()
{
	return m_LuaContext;
}

//sync communication
std::shared_ptr<IASObject> CScheduler::syncCommand(std::shared_ptr<IASObject> arg)
{
	if (DEBUG) cout << "call syncCommand" << endl;

	std::string modulePara = arg->stringData();
	std::string commandStr = arg->commandString();

	LuaContext* lua = CScheduler::luaContext();
	
	std::string funcStr;
	funcStr = "return " + commandStr + "(\"" + modulePara + "\")";

	if (DEBUG) cout << "sync funcStr : " << funcStr << endl;

	std::string luaRet;
	try
	{
		luaRet = lua->executeCode<std::string>(funcStr.c_str());
		if (DEBUG) cout << "sync Success : " << luaRet << endl;
	}
	catch (const exception &e) {
		printf("load %s exception:%s\n", commandStr.c_str(), e.what());
		return nullptr;
	}

 	//std::shared_ptr<CMyTask> retTask = std::make_shared<CMyTask>();
// 	retTask->setCommandString(commandStr);
// 	retTask->setStringData(luaRet.c_str());
	arg->setStringData(luaRet.c_str());

    return arg;
}

//async communication
bool CScheduler::asyncCommand(std::shared_ptr<IASObject> arg)
{
	if(DEBUG)cout << "call asynCommand" << endl;

	CTaskThread* taskThread = GetTaskThread();

	do
	{
		CHECK_POOL_SURVIVE(m_bSurvive);

		std::lock_guard<std::mutex> lock(taskThread->TaskMutex());

		taskThread->TaskList().push_back(arg);

		taskThread->SemTask().Signal();

	} while (0);

    return true;
}

//add notify command to queue
bool CScheduler::addEventListen(std::shared_ptr<IASObject> arg)
{
	CTaskThread* taskThread = GetTaskThread();

	do
	{
		CHECK_POOL_SURVIVE(m_bSurvive);

		std::lock_guard<std::mutex> lock(taskThread->NotifyMutex());
		taskThread->NotifyList().push_back(arg);

	} while (0);

    return true;
}

CTaskThread* CScheduler::GetTaskThread()
{
	return m_ThreadTask;
}

CMessageThread* CScheduler::GetMsgThread()
{
	return m_ThreadMessage;
}
