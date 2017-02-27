//
// Created by Administrator on 2017/2/27 0027.
//

#ifndef CORE_OBJECTCONTAINER_H
#define CORE_OBJECTCONTAINER_H

#include <list>
#include <IASObject.h>

namespace TBAS
{
    namespace Core
    {
        class ObjectContainer
        {
        public:
            ObjectContainer();
            ~ObjectContainer();
            unsigned int Size();
            void Push(std::week_ptr<IASObject> asObject);
            std::week_ptr<IASObject> Top();
            void Pop();
            void Erase(std::week_ptr<IASObject> asObject);

        private:
            std::list<std::week_ptr<IASObject>> object_container_;

        };
    }
}

#endif //CORE_OBJECTCONTAINER_H
