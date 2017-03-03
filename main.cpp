#include <iostream>
#include "Scheduler.h"
#include "IASObject.h"
#include "MyTask.h"

using namespace std;
using namespace TBAS::Core;

void fuck(std::shared_ptr<IASObject> asObject)
{
	cout << "Success call-back : " << asObject->stringData() << endl;
}

int main() 
{
    //std::cout << "Hello, World!" << std::endl;
	Scheduler* scheduler = Scheduler::instance();

	std::this_thread::sleep_for(std::chrono::seconds(3));

	std::shared_ptr<MyTask> task = std::make_shared<MyTask>();

	task->setCommandString("config:test");
	task->setStringData("fuckyou");
	task->onCommandTaskSuccess = fuck;
	//cout << "----:" << task->stringData() << endl;

	//cout << "before asyn" << endl;
	scheduler->asyncCommand(task);
	//cout << "end asyn" << endl;


    return 0;
}