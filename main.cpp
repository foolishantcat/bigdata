// 测试文件
#include <stdio.h>
#include <memory>
#include "Config.h"
#include "CScheduler.h"
#include "CMyTask.h"
#include "LuaContext.hpp"

using namespace std;
using namespace TBAS;
using namespace TBAS::Core;

void fuck(std::shared_ptr<IASObject> asObject)
{
	cout << "Success call-back : " << asObject->stringData() << endl;
}

void testLua()
{
	

}

void testAsync()
{
	CScheduler* scheduler = CScheduler::instance();
	auto config = Config::instance();


	std::this_thread::sleep_for(std::chrono::seconds(3));

	std::shared_ptr<CMyTask> task = std::make_shared<CMyTask>();

	task->setCommandString("config:cmdstring");
	task->setStringData("login");
	task->onCommandTaskSuccess = fuck;
	//cout << "----:" << task->stringData() << endl;

	//cout << "before asyn" << endl;
	scheduler->asyncCommand(task);

	std::this_thread::sleep_for(std::chrono::seconds(3));
	scheduler->release();
}

void testSysnc()
{
	CScheduler* scheduler = CScheduler::instance();

	std::this_thread::sleep_for(std::chrono::seconds(3));

	std::shared_ptr<CMyTask> task = std::make_shared<CMyTask>();

	task->setCommandString("option_servive");
	task->setStringData("");

	std::shared_ptr<IASObject> ret = scheduler->syncCommand(task);

	scheduler->release();
}

void testConfig()
{
	CScheduler* scheduler = CScheduler::instance();

	Config* config = Config::instance();
	LuaContext* lua = CScheduler::luaContext();

	config->setConfigDir(".");
	config->setVersion("ios", "10", "iphone6", "0.0.1", "0.0.1");

	if (config->loadConfig("ios", "0.0.1", lua) == 0)
	{
		printf("load config ok\n");
	}
	else
	{
		printf("load config failed\n");
	}

	config->unloadModule("option_service.lua", lua);

	scheduler->release();
}

int main() 
{
	testSysnc();

	testAsync();

	testLua();

    return 0;
}
