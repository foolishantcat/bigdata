//
// Created by Administrator on 2017/2/24 0024.
//

//Link Task

#ifndef TBAS_CORE_IAS_CORE_TYPE_H
#define TBAS_CORE_IAS_CORE_TYPE_H

namespace TBAS
{
    namespace Core
    {
        class IASObject{
        public:
            //call back
            std::function<void(std::shared_ptr<IASObject> asObject)> onCommandTaskSuccess;
            nlohmann::json jsonData;
            virtual std::string errorInfo(){ return "";};
            virtual int errorNumber(){ return 0;};
            virtual std::string commandString() { return "";};
            virtual void setData(void *data) {} ;
            virtual void * const data(){return nullptr;};
            /*! Virtual destructor */
            virtual ~IASObject() {};
        };
    }
}

#endif //TBAS_CORE_IAS_CORE_TYPE_H
