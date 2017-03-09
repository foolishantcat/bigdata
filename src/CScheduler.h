//
// Created by caoyc on 2017/2/24 0024.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <thread>
#include <memory>
#include "IASObject.h"
#include "Config.h"
#include "LuaContext.hpp"
#include "CTaskThread.h"
#include "CMessageThread.h"

namespace TBAS {
    namespace Core {

        class CScheduler {
        public:
            static CScheduler *instance();
            static const char* version();
			static LuaContext* luaContext();

            std::shared_ptr<IASObject> syncCommand(std::shared_ptr<IASObject> arg);
            bool asyncCommand(std::shared_ptr<IASObject> arg);
            bool addEventListen(std::shared_ptr<IASObject> arg);

			bool release();

			CTaskThread* GetTaskThread();
			CMessageThread* GetMsgThread();

        private:
            CScheduler();
            virtual ~CScheduler();
            static const char* versionInfo;
            static CScheduler* schedulerShared;

            class SchedulerGarbo
            {
            public:
                ~SchedulerGarbo()
                {
                    if (CScheduler::schedulerShared)
                        delete CScheduler::schedulerShared;
                }
            };
            static SchedulerGarbo Garbo;
			static Config* m_Config;
			static LuaContext* m_LuaContext;

			bool m_bSurvive;

			CTaskThread* m_ThreadTask;
			CMessageThread* m_ThreadMessage;
			int m_ThreadNums;

			std::thread m_Thread;

			std::mutex m_Mutex;
			std::mutex m_SyncMutex;		//同步接口锁
        };
	} //end for namespace Core

} //end for namespace TBAS

#endif //SCHEDULER_H
