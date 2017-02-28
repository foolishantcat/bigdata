//
// Created by Administrator on 2017/2/27 0027.
//

#include "Common.h"
#include "TaskQueue.h"

TaskQueue::TaskQueue(TaskQueueContainer* container)
{
    object_list_.clear();
    number_of_task_ = 0;
    task_queue_container_ = container;
}

TaskQueue::~TaskQueue()
{

}

int TaskQueue::Size()
{
    return object_list_.size();
}

void TaskQueue::Push(std::week_ptr<IASObject> asObject)
{
    do
    {
        //if(auto observe = asObject.lock())
            //break;
        CHECK_WEEK_PTR_VALID(asObject);

        //add mutex lock
        CoreLock Lock(&task_queue_container_.task_mutex_);
        object_list_.push_back(asObject);

    } while(0);
}

std::week_ptr<IASObject> TaskQueue::Top()
{
    return object_list_.front();
}

//delete top elememt
void TaskQueue::Pop()
{
    object_list_.pop_front();
}

bool TaskQueue::Empty()
{
    return object_list_.empty();
}