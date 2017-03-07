//
// Created by caoyc on 2017/2/27 0027.
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
        class CMyTask : public IASObject, public std::enable_shared_from_this<CMyTask>
        {
        public:
            CMyTask();
            ~CMyTask();

			void setError(std::string errorInfo, int errorNumber);
            std::string errorInfo();
            int errorNumber();

			void setCommandString(std::string commandStr);
            std::string commandString();

            void setData(void *data);
            void * const data();

			void setStringData(std::string strData);
			std::string stringData();

        private:
            void *m_data_;
			std::string m_stringData;
            std::string m_command_;
			std::string m_errorinfo_;
			int error_number_;
        };
    }
}

#endif //MYTASK_H_H
