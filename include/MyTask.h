//
// Created by Administrator on 2017/2/27 0027.
//

#ifndef MYTASK_H_H
#define MYTASK_H_H

#include <string>
#include <memory>
#include "IASObject.h"

namespace TBAS
{
    namespace Core
    {
        class MyTask : public IASObject, public std::enable_shared_from_this<MyTask>
        {
        public:
            MyTask();
            MyTask(std::string commandString);      //set command string
            virtual ~MyTask();
            std::string errorInfo();
            int errorNumber();
            std::string commandString();
            void setData(void *data);
            void * const data();

        private:
            void *m_data;
            std::string m_command;
        };
    }
}

#endif //CORE_MYTASK_H_H
