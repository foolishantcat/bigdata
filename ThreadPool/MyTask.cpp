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

MyTask::~MyTask()
{

}

std::string MyTask::errorInfo()
{
	return m_errorinfo_;
}

void MyTask::setError(std::string errorInfo, int errorNumber)
{
	m_errorinfo_.assign(errorInfo);
	error_number_ = errorNumber;
}

int MyTask::errorNumber()
{
	return error_number_;
}

void MyTask::setCommandString(std::string commandStr)
{
	m_command_.assign(commandStr);
}

std::string MyTask::commandString()
{
	return m_command_;
}

void MyTask::setStringData(std::string strData)
{
	m_stringData.assign(strData);
}

std::string MyTask::stringData()
{
	return m_stringData;
}

void MyTask::setData(void* data)
{
	m_data_ = data;
}

void* const MyTask::data()
{
	return m_data_;
}


