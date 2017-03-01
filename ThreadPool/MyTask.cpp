//
// Created by Administrator on 2017/2/24 0024.
//

#include <string>
#include "MyTask.h"

using namespace std;
using namespace TBAS::Core;

MyTask::MyTask()
{

}

MyTask::MyTask(std::string commandString)
{

}

MyTask::~MyTask()
{

}

std::string MyTask::errorInfo()
{
	return nullptr;
}

int MyTask::errorNumber()
{
	return 0;
}

std::string MyTask::commandString()
{
	return nullptr;
}

void MyTask::setData(void* data)
{

}

void* const MyTask::data()
{
	return nullptr;
}


