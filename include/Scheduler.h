//
// Created by Administrator on 2017/2/24 0024.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <thread>
#include <memory>
#include "IASObject.h"
#include "CoreThreadPool.h"

//class TBAS::Core::CoreThreadPool;

namespace TBAS {
    namespace Core {

        class Scheduler {
        public:
            static Scheduler *instance();
            static const char* version();

            std::shared_ptr<IASObject> syncCommand(std::shared_ptr<IASObject> arg);
            bool asyncCommand(std::shared_ptr<IASObject> arg);
            bool addEventListen(std::shared_ptr<IASObject> arg);
        private:
            Scheduler();
            virtual ~Scheduler();
            static const char* versionInfo;
            static Scheduler* schedulerShared;

            class SchedulerGarbo
            {
            public:
                ~SchedulerGarbo()
                {
                    if (Scheduler::schedulerShared)
                        delete Scheduler::schedulerShared;
                }
            };
            static SchedulerGarbo Garbo;
            static CoreThreadPool* threadPool;
        };
	} //end for namespace Core

} //end for namespace TBAS

#endif //SCHEDULER_H
