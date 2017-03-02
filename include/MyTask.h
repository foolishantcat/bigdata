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
            ~MyTask();

			void setError(std::string errorInfo, int errorNumber);
            std::string errorInfo();
            int errorNumber();

			void setCommandString(std::string commandStr);
            std::string commandString();

            void setData(void *data);		//ignore this
            void * const data();			//ignore this

			void setStringData(std::string strData);	//lua para
			std::string stringData();

        private:
            void *m_data_;			//ignore this
			std::string m_stringData;
            std::string m_command_;
			std::string m_errorinfo_;
			int error_number_;
        };
    }
}

#endif //MYTASK_H_H
