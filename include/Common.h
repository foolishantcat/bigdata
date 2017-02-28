//
// Created by Administrator on 2017/2/28 0028.
//

#ifndef CORE_COMMON_H
#define CORE_COMMON_H

namespace TBAS
{
    namespace Core
    {
#define NUMBER_OF_THREAD 2
#define NUMBER_OF_TASK_QUEUE 3
#define CHECK_POOL_SURVIVE(is_survive) if(true != is_survive) \
            break;
#define CHECK_WEEK_PTR_VALID(ptr) if(auto observe = ptr.lock()) \
            break;

    }
}

#endif //CORE_COMMON_H
