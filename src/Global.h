//
// Created by caoyc on 2017/2/28 0028.
//

#ifndef GLOBAL_H
#define GLOBAL_H

#define NUMBER_OF_THREAD 2
#define NUMBER_OF_TASK_QUEUE 3
#define CHECK_POOL_SURVIVE(is_survive) if(true != is_survive) \
            break;
#define CHECK_WEEK_PTR_VALID(ptr) if(auto observe = ptr.lock()) \
            ; \
		else \
			break;
#define QUEUE_TASK_ID 0
#define QUEUE_NOTIFY_ID 1
#define QUEUE_MESSAGE_ID 2

#define THREAD_TASK_ID 1
#define THREAD_MESSAGE_ID 2


#endif //GLOBAL_H
