//
// Created by caoyc on 2017/2/24 0024.
//

//Link Task

#ifndef IAS_OBJECT_H
#define IAS_OBJECT_H

#include "json.hpp"

namespace TBAS
{
    namespace Core
    {
        class IASObject{
        public:
            //call back
            std::function<void(std::shared_ptr<IASObject> asObject)> onCommandTaskSuccess;
			nlohmann::json jsonData;

			virtual void setError(std::string errorInfo, int errorNumber) {};
            virtual std::string errorInfo(){ return "";};
            virtual int errorNumber(){ return 0;};

			virtual void setCommandString(std::string commandStr) {};
            virtual std::string commandString() { return "";};

            virtual void setData(void *data) {} ;
            virtual void * const data(){return nullptr;};

			virtual void setStringData(std::string strData) {};
			virtual std::string stringData() { return ""; };
            /*! Virtual destructor */
            virtual ~IASObject() {};
        };
    }
}

#endif //IAS_OBJECT_H
