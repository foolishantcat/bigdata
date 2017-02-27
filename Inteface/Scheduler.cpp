//
// Created by Administrator on 2017/2/24 0024.
//
#include "Scheduler.h"
#include "CoreThreadPool.h"
using namespace TBAS::Core;

Scheduler::Scheduler()
{

}

//relaese
Scheduler::~Scheduler()
{

}

//instance core frame
static Scheduler* Scheduler::instance()
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
            threadPool = new CoreThreadPool(NUMBER_OF_THREAD);

        //start thread pool
        threadPool->Start();

    } while (0);

    return schedulerShared;
}

//get version
static const char* Scheduler::version()
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
