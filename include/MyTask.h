//
// Created by Administrator on 2017/2/27 0027.
//

#ifndef CORE_MYTASK_H_H
#define CORE_MYTASK_H_H

#include <string>
#include "IASObject.h"

namespace TBAS
{
    namespace Core
    {
        class MyTask : public IASObject
        {
        public:
            MyTask();
            virtual ~MyTask();
            std::string errorInfo();
            int errorNumber();
            std::string commandString();
            void setData(void *data);
            void * const data();
        };
    }
}

#endif //CORE_MYTASK_H_H
