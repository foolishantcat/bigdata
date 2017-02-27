//
// Created by Administrator on 2017/2/24 0024.
//

#ifndef TBAS_CORE_SCHEDULERGARBO_H
#define TBAS_CORE_SCHEDULERGARBO_H

namespace TBAS
{
    namespace Core
    {
        class SchedulerGarbo
        {
        public:
            ~SchedulerGarbo()
            {
                if (Scheduler::schedulerShared)
                    delete Scheduler::schedulerShared;
            }
        };

    }

}


#endif //TBAS_CORE_SCHEDULERGARBO_H
