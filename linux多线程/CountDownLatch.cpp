#include<iostream>
#include<mutex>
#include"boost/noncopyable.hpp"

using  namespace std;


class mutexLock {
public:
	mutexLock(mutex& _mutex) :_mutex(_mutex) {
		_mutex.lock();
	}
	~mutexLock() {

	}
private:
	mutex & _mutex;
};


class CountDownLatch:public boost::noncopyable {
public:
	CountDownLatch(int c) :count(c) {};
	void countdown() {
		mutexLock Lock(_mutex);
		count--;
		if (count == 0) {
			condition.notifyAll();//里面带一个循环 把condition的计数器加上c
		}
		
	}
	void wait(){
		mutexLock Lock(_mutex);
		if (count > 0)condition.wait();
	}
private:
	mutex _mutex;
	int count;
	muduo::Condition condition;
};


int main() {

	return 0;
}