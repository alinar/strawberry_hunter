#pragma once
#include <list>
#include <mutex>

/*class template*/
template<typename T>
class LockyList:public std::list<T>{
	private:
	mutable std::mutex mtx;
        public:
	void lock(){
		mtx.lock();
	}
	void unlock(){
		mtx.unlock();
	}
	bool try_lock(){
		return mtx.try_lock();
	}
};
