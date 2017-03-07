//
// Created by caoyc on 2017/2/24 0024.
//

#ifndef CORE_THEAD_H
#define CORE_THEAD_H

#include <list>
#include <thread>
#include "IASObject.h"

namespace TBAS
{
    namespace Core
    {
        class CThread
        {
		public:
			bool Start();
			void Stop();
		public:
			static void* ThreadProc(void* lvpContex);

		protected:
			virtual void OnRun() = 0;
			virtual bool OnInitThread() = 0;

        public:
			CThread();
            virtual ~CThread();

        private:
            std::thread m_Thread_;

        };
    }
}

#endif //CORE_THEAD_H
