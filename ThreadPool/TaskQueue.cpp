//
// Created by Administrator on 2017/2/27 0027.
//

#include "Common.h"
#include "TaskQueue.h"
#include "CoreLock.h"

using namespace TBAS::Core;

TaskQueue::TaskQueue(TaskQueueContainer* container)
{
    object_list_.clear();
	wk_object_list_.clear();
    number_of_task_ = 0;
    task_queue_container_ = container;
}

TaskQueue::~TaskQueue()
{

}

unsigned int TaskQueue::Size()
{
	if (false == is_weak_ptr_)
		return object_list_.size();
	else
		return wk_object_list_.size();
}

void TaskQueue::Push(std::weak_ptr<IASObject> asObject)
{
    do
    {
        //add mutex lock
        //CoreLock Lock(&(task_queue_container_->task_mutex_));
		if(false == is_weak_ptr_)
		{
			CHECK_WEEK_PTR_VALID(asObject);
			object_list_.push_back(asObject.lock());
		}
		else
			wk_object_list_.push_back(asObject);

    } while(0);
}

std::weak_ptr<IASObject> TaskQueue::Top()
{
	if (true == is_weak_ptr_)
		return wk_object_list_.front();
	else
		return object_list_.front();
}

//pop top elememt
void TaskQueue::Pop()
{
	if (true == is_weak_ptr_)
		wk_object_list_.pop_front();
	else
		object_list_.pop_front();
}

bool TaskQueue::Empty()
{
	if (true == is_weak_ptr_)
		return wk_object_list_.empty();
	else
		return object_list_.empty();
}

//simplify handle ,just delete notify queue
void TaskQueue::Erase(std::list<std::weak_ptr<IASObject>>::iterator it)
{
	if (true == is_weak_ptr_)
		wk_object_list_.erase(it);
}
