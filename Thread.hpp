/*********************************************************
 * Author           : crazy_mad
 * Last modified    : 2017-04-21 00:13
 * Filename         : Thread.h
 * Description      : 
 *********************************************************/

#ifndef _THREAD_H
#define _THREAD_H

#include <pthread.h>
#include <boost/function.hpp>

//#include "Mutex.hpp"

typedef boost::function<void ()> Callback;			// 回调函数
void* runInThread(void *obj); 

class Thread {
public:
	Thread() {
		pthread_create(&thread_fd, NULL, runInThread, this);
   	}
	void start(boost::function<void ()> cb) {									// 开启线程
		this->cb = cb;
		isRunning = true;
	}
	void join() {									// 使主线程等待子线程结束(阻塞)
		pthread_join(thread_fd, NULL);				
	}
	void run() {
		cb();
		isRunning = false;
	}
	bool statu() {		
		return isRunning;		
	}

private:
	pthread_t thread_fd;
	boost::function<void ()> cb;
	bool isRunning;
};

void* runInThread(void *obj) {
	Thread *thread_ = static_cast<Thread*>(obj);
	while (thread_->statu()) {
		while (!thread_->statu()) {
			;
		}
		thread_->run();
	}
	return NULL;
}

#endif

