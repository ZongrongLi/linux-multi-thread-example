#include<iostream>
#include<mutex>
#include<queue>
using namespace std;
mutex _mutex;
muduo::condition con(mutex);
deque<int> q;
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


void enqueue(int c) {
	mutexLock L(_mutex);
	q.push_back(c);
	cond.notify();
}

int dequeue() {
	mutexLock L(_mutex);
	while (q.empty())cond.wait();
	assert(!q.empty());
	return q.pop_front();

}

int main() {

	return 0;
}