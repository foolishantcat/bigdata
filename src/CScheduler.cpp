//
// Created by caoyc on 2017/2/24 0024.
//
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "CScheduler.h"
#include "Global.h"
#include "CThreadPool.h"
#include "LuaContext.hpp"
#include "CMyTask.h"

using namespace std;
using namespace TBAS::Core;
using namespace TBAS;

CScheduler::CScheduler() 
{
	cout << "Get scheduler instance..." << endl;
}
CScheduler::~CScheduler() 
{
	//threadPool->EndCoreThreadPool();
	cout << "~Scheduler\n";
}

bool CScheduler::release()
{
	cout << "before threadpool->release()" << endl;
	m_ThreadPool->Release();
	cout << "after threadpool->release()" << endl;

	delete m_LuaContext;

	return true;
}

//For instance and de-construction
CScheduler *CScheduler::schedulerShared = NULL;
CScheduler::SchedulerGarbo CScheduler::Garbo;
CThreadPool* CScheduler::m_ThreadPool = NULL;
const char* CScheduler::versionInfo = NULL;
Config* CScheduler::m_Config = NULL;
LuaContext* CScheduler::m_LuaContext = NULL;

//instance core frame
CScheduler* CScheduler::instance()
{
	//cout << "Scheduler::instance()" << endl;
    do
    {
        //get version info

        //instance Core
        if(NULL != schedulerShared)
            break;
        else
            schedulerShared = new CScheduler();

        //init thread pool
        if(NULL != m_ThreadPool)
            break;
        else
            m_ThreadPool = CThreadPool::CreateThreadPool(NUMBER_OF_THREAD, schedulerShared);

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
	cout << "call syncCommand" << endl;

	std::string modulePara = arg->stringData();
	std::string commandStr = arg->commandString();
	ostringstream ostr;
	ostr << commandStr << "(" << modulePara << ")" << endl;
	LuaContext* lua = CScheduler::luaContext();
	std::ifstream ifs("option_service.lua");
	ifs.close();

	//lua->executeCode(ifs.get());

// 	Config* luaConfig = Config::instance();
// 	std::string func;
// 	if (luaConfig->findFunction(commandStr, func))
// 	{
// 		cout << "Success: " << func << endl;
// 	}
// 	else
// 	{
// 
// 	}
// 
//  	const auto function = lua->readVariable<std::function<std::string(void)>>("execute");
//  	std::string luaRet = function();
// 
// 	if (!luaRet.empty())
// 	{
// 		cout << "Success : " << luaRet << endl;
// 	}
// 	else
// 	{
// 		cout << "Failed : " << luaRet << endl;
// 	}
// 
 	std::shared_ptr<CMyTask> retTask = std::make_shared<CMyTask>();
// 	retTask->setCommandString(commandStr);
// 	retTask->setStringData(luaRet.c_str());

    return retTask;
}

//async communication
bool CScheduler::asyncCommand(std::shared_ptr<IASObject> arg)
{
	cout << "call asynCommand" << endl;
	m_ThreadPool->AddTask(arg);

    return true;
}

//add notify command to queue
bool CScheduler::addEventListen(std::shared_ptr<IASObject> arg)
{
	m_ThreadPool->AddNotify(arg);


    return true;
}
