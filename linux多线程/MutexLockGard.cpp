#include<iostream>
#include"boost/noncopyable.hpp"

using namespace std;

class MutexLock:boost::noncopyable{
public:
	MutexLock():holder(0) {
		pthread_mutex_init(&_mutex,NULL);
		
	}
	~MutexLock() {
		assert(holder == 0);
		pthread_mutex_destroy(&_mutex);
	}
	lock() {
		pthread_mutex_lock(&_mutex);
		holder = CurrentThread_id;
	}
	unlock() {
		holder = 0;
		pthread_mutex_unlock(&_mutex);
	}

private:
	pid_t holder;
	pthread_mutex_t _mutex;
};


class MutexLockGuard :public boost::noncopyable {
	explicit MutexLockGuard(MutexLock& t):_mutex(t){
		_mutex.lock();
	}
	~MutexLockGuard() {
		_mutex.unlock();
	}
private:
	MutexLock & _mutex;
};
#define MutexLockGuard(x) static_assert(false,"missing mutex guard var name")
int main() {

	return 0;
}