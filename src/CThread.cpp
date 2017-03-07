//
// Created by caoyc on 2017/2/27 0027.
//

#include <list>
#include <memory>
#include <fstream>
#include <iostream>
#include "Global.h"
#include "CThread.h"
#include "CThreadPool.h"
#include "CLock.h"
#include "CMyTask.h"
#include "LuaContext.hpp"

using namespace std;
using namespace TBAS::Core;

CThread::CThread()
{
	
}

CThread::~CThread()
{

}

bool CThread::Start()
{
	cout << "CThread::Start()" << endl;
	if (!OnInitThread())
	{
		return false;
	}

    std::thread thread_new = std::thread(&CThread::ThreadProc, this);

	m_Thread_ = std::move(thread_new);

	return true;
}

void CThread::Stop()
{
	if (m_Thread_.joinable())
	{
		cout << "before join ::[ " << m_Thread_.get_id() << "] | " << endl;
		m_Thread_.join();
		cout << "after join..." << endl;
	}
}

void* CThread::ThreadProc(void* lpvContex)
{
	CThread* lpInstance = NULL;
	cout << "CThread::ThreadProc()" << endl;
	lpInstance = (CThread*)lpvContex;
	lpInstance->OnRun();

	return (void*)1;
}