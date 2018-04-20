#include<iostream>
#include<stdio.h>
#include<string>
#include<memory>
#include<mutex>
#include<map>
#include"boost/enable_shared_from_this.hpp"

using namespace std::placeholders;
using namespace std;
class stock {

};
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
class stockfactory :public boost::enable_shared_from_this<stockfactory> {
public:
	shared_ptr<stock> get(const string s) {
		weak_ptr<stock> &wp = mp[s];
		shared_ptr<stock> p = wp.lock();
		if (!p) {
			mutexLock t(_mutex);
			p.reset(new stock(),
				bind(&stockfactory::deleteP, boost::weak_ptr<stockfactory>(shared_from_this()), _1));
			wp = p;
		}

		return p;
	}
private:
	static void deleteP(const boost::weak_ptr<stockfactory>& wp, stock *t) {
		boost::shared_ptr<stockfactory> p(wp.lock());
		if (p) {
			//	mutexLock t(_mutex);
			//remove from mp;
			return;
		}
		delete t;

	}
private:
	map<string, weak_ptr<stock> > mp;
	mutable mutexLock _mutex;
};
int main() {

	return 0;
}
