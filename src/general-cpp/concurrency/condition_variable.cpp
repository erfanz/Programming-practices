/*
A condition variable manages a list of threads waiting until another thread notify them.
Each thread that wants to wait on the condition variable has to acquire a lock first.
The lock is then released when the thread starts to wait on the condition and the lock is
acquired again when the thread is awakened.
*/

/*
Our program manages a bounded buffer with consumers and providers
*/



#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <iostream>

using namespace std;

class BoundedBuffer {
private:
	vector<pair<int, int>> buffer_;	// we define each element of our buffer as a pair of producerID and itemID
	mutex lock_;
	condition_variable notFull_;
	condition_variable notEmpty_;
	int maxCapacity_;
	int currentSize_;
	
public:
	BoundedBuffer(int maxCapacity): buffer_(maxCapacity), maxCapacity_(maxCapacity), currentSize_(0) {}
	
	void deposit(int pID, int itemID){
		unique_lock<mutex> lck(lock_);
		
		// "wait" method blocks the current thread until the condition variable is woken up (either notified or spurious wakup occurs)
		// after the wakeup, the predicate (2nd arg of wait function) is checked, and if it's false, the threads goes back to sleep
		// Also, when going to sleep, it releases the lock. When woken up (either notified or spurious wakeup), it reacquires the lock.
		notFull_.wait(lck, [this](){return currentSize_ != maxCapacity_; });	 
	
		// at this point, the thread has woken up, the buffer is not full, and the mutex has been reacquired
		buffer_[currentSize_] = make_pair(pID, itemID);
		currentSize_++;
		
		// now that the buffer is definitely non-empty, we need to wake up the consumers
		lck.unlock();
		notEmpty_.notify_one();
	}
	
	pair<int, int> fetch() {
		unique_lock<mutex> lck(lock_);
		
		notEmpty_.wait(lck, [this](){return currentSize_ > 0; });
		
		// at this point, the thread has woken up, the buffer is non-empty, and the mutex has been reacquired.
		auto result = buffer_[currentSize_ - 1];
		--currentSize_;
		
		// now that the buffer is definitely not full, we need to wake up the producers
		lck.unlock();
		notFull_.notify_one();
		
		return result;
		
	}
	
};


void produce(int pID, BoundedBuffer &buffer) {
	for (int i = 0; i < 100; i++) {
		buffer.deposit(pID, i);
		cout << "Produced " << pID << " produced " << i << endl;
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

void consume(int cID, BoundedBuffer &buffer) {
	for (int i = 0; i < 60; i++) {
		auto fetched = buffer.fetch();
		cout << "Consumer " << cID <<  " consumed " << fetched.first << "-" << fetched.second  << endl;
		this_thread::sleep_for(chrono::milliseconds(200));
	}
}


int main(){
	BoundedBuffer bbuffer(100);
	
	// std::ref is necessary to pass the buffer by reference, otherwise it copies the buffer.	
	std::thread c1(consume, 0, std::ref(bbuffer));
	std::thread c2(consume, 1, std::ref(bbuffer));
	std::thread c3(consume, 2, std::ref(bbuffer));
	std::thread p1(produce, 0, std::ref(bbuffer));
	std::thread p2(produce, 1, std::ref(bbuffer));
	
	c1.join();
	c2.join();
	c3.join();
	p1.join();
	p2.join();
	
	return 0;
}
