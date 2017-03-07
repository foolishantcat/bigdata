#include <iostream>
#include "CScheduler.h"
#include "IASObject.h"
#include "CMyTask.h"

using namespace std;
using namespace TBAS::Core;

void fuck(std::shared_ptr<IASObject> asObject)
{
	cout << "Success call-back : " << asObject->stringData() << endl;
}

int main() 
{
    //std::cout << "Hello, World!" << std::endl;
	CScheduler* scheduler = CScheduler::instance();

	std::this_thread::sleep_for(std::chrono::seconds(3));

	std::shared_ptr<CMyTask> task = std::make_shared<CMyTask>();

	task->setCommandString("config:test");
	task->setStringData("fuckyou");
	task->onCommandTaskSuccess = fuck;
	//cout << "----:" << task->stringData() << endl;

	//cout << "before asyn" << endl;
	scheduler->asyncCommand(task);
	//cout << "end asyn" << endl;

	std::this_thread::sleep_for(std::chrono::seconds(3));
	scheduler->release();

    return 0;
}