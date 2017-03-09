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

//需要一个回调函数，这是用来测试的
void fuck(std::shared_ptr<IASObject> asObject)
{
	cout << "Success call-back : " << asObject->stringData() << endl;
}

void testConfig_Async_Sync()
{
	CScheduler* scheduler = CScheduler::instance();

	//以下是配置步骤，程序起来，仅需配置一次
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

	//以下是调用模块步骤，更换模块函数，需要修改如下代码
	std::string cmdstring = "login";
	std::string func;

	config->findFunction(cmdstring, func);

	std::cout << "return func string : {" << func << "}" << endl;

	//模拟异步调用
	std::shared_ptr<CMyTask> task = std::make_shared<CMyTask>();

	task->setCommandString(func);
	task->setStringData("fuck");

	task->onCommandTaskSuccess = fuck;

	scheduler->asyncCommand(task);

	//模拟同步调用
	std::shared_ptr<CMyTask> task_1 = std::make_shared<CMyTask>();
	task_1->setCommandString(func);
	task_1->setStringData("fuck");
	task_1->onCommandTaskSuccess = NULL;
	scheduler->syncCommand(task_1);

	//卸载当前模块是必要的
	config->unloadModule("config.lua", lua);
	config->unloadModule("option_service.lua", lua);
	config->unloadModule("depend_service.lua", lua);

	//这个最后退出app调用
	scheduler->release();
}

void testConfig_Sync()
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

	std::string cmdstring = "login";
	std::string func;

	config->findFunction(cmdstring, func);

	std::cout << "return func string : {" << func << "}" << endl;

	std::shared_ptr<CMyTask> task = std::make_shared<CMyTask>();

	task->setCommandString(func);
	task->setStringData("imay_success");

	scheduler->syncCommand(task);

	config->unloadModule("config.lua", lua);
	config->unloadModule("option_service.lua", lua);
	config->unloadModule("depend_service.lua", lua);

	scheduler->release();
}

int main() 
{
	//CScheduler* scheduler = CScheduler::instance();
	testConfig_Async_Sync();

	testConfig_Sync();

    return 0;
}
