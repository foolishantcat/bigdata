//
// Created by caoyc on 2017/2/24 0024.
//

#ifndef CORE_THREAD_POOL_H
#define CORE_THREAD_POOL_H

#include <list>
#include <thread>
#include "Global.h"
#include "IASObject.h"
#include "CMessageThread.h"
#include "CSemaphore.h"
#include "CTaskThread.h"

namespace TBAS
{
    namespace Core
    {
		class CScheduler;
        class CThreadPool
        {
        public:
			typedef std::shared_ptr<IASObject> TASK_OBJ;
			typedef std::weak_ptr<IASObject> TASK_OBJ_WK;
			typedef std::mutex CMutex;

			static CThreadPool* CreateThreadPool(int number = 2, CScheduler* pScheduler = NULL);
            void AddTask(TASK_OBJ asObject);
			void AddNotify(TASK_OBJ_WK asObject);
			void Clear();
			void Release();

		public:
			CTaskThread* GetTaskThread();
			CMessageThread* GetMsgThread();

		private:
			CThreadPool();
			~CThreadPool();

        private:
            bool m_bSurvive;

            CScheduler* scheduler_;

			CTaskThread* m_ThreadTask;
			CMessageThread* m_ThreadMessage;
			int m_ThreadNums;

            std::thread m_Thread;

            CMutex m_Mutex;
        };

    }

}

#endif //CORE_THREAD_POOL_H
