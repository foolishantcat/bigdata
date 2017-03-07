//
// Created by caoyc on 2017/2/24 0024.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <thread>
#include <memory>
#include "IASObject.h"
#include "CThreadPool.h"
#include "Config.h"
#include "LuaContext.hpp"

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
            static CThreadPool* m_ThreadPool;
			static Config* m_Config;
			static LuaContext* m_LuaContext;
        };
	} //end for namespace Core

} //end for namespace TBAS

#endif //SCHEDULER_H
