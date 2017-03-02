//
// Created by Administrator on 2017/2/24 0024.
//
#include "Scheduler.h"
#include "Common.h"
#include "CoreThreadPool.h"

using namespace TBAS::Core;

Scheduler::Scheduler() {}
Scheduler::~Scheduler() {}

//For instance and de-construction
Scheduler *Scheduler::schedulerShared = NULL;
Scheduler::SchedulerGarbo Scheduler::Garbo;
CoreThreadPool* Scheduler::threadPool = NULL;
const char* Scheduler::versionInfo = NULL;
//instance core frame
Scheduler* Scheduler::instance()
{
    do
    {
        //get version info

        //instance Core
        if(NULL != schedulerShared)
            break;
        else
            schedulerShared = new Scheduler();

        //init thread pool
        if(NULL != threadPool)
            break;
        else
            threadPool = new CoreThreadPool(NUMBER_OF_THREAD, schedulerShared);

        //start thread pool
        threadPool->Init();
        threadPool->Run();

    } while (0);

    return schedulerShared;
}

//get version
const char* Scheduler::version()
{
    //get version info

    return versionInfo;
}

//sync communication
std::shared_ptr<IASObject> Scheduler::syncCommand(std::shared_ptr<IASObject> arg)
{
    //use multi-thread c++11


    return nullptr;
}

//async communication
bool Scheduler::asyncCommand(std::shared_ptr<IASObject> arg)
{
    //use call-back func

    return false;
}

//message communication
bool Scheduler::addEventListen(std::shared_ptr<IASObject> arg)
{
    return false;
}
