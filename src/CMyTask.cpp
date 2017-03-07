//
// Created by caoyc on 2017/2/24 0024.
//

#include <string>
#include "CMyTask.h"

using namespace std;
using namespace TBAS::Core;

CMyTask::CMyTask()
{
	m_data_ = NULL;
	error_number_ = -1;
}

CMyTask::~CMyTask()
{

}

std::string CMyTask::errorInfo()
{
	return m_errorinfo_;
}

void CMyTask::setError(std::string errorInfo, int errorNumber)
{
	m_errorinfo_.assign(errorInfo);
	error_number_ = errorNumber;
}

int CMyTask::errorNumber()
{
	return error_number_;
}

void CMyTask::setCommandString(std::string commandStr)
{
	m_command_.assign(commandStr);
}

std::string CMyTask::commandString()
{
	return m_command_;
}

void CMyTask::setStringData(std::string strData)
{
	m_stringData.assign(strData);
}

std::string CMyTask::stringData()
{
	return m_stringData;
}

void CMyTask::setData(void* data)
{
	m_data_ = data;
}

void* const CMyTask::data()
{
	return m_data_;
}


