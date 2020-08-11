#include <thread>
#include <future> // for async and Future
#include <iostream>
#include <vector>
#include <cassert>
#include <numeric> // for accumulate
 
using namespace std;

void addNumbersForThread(int* data, size_t count, int &result) {
	// sums up elements
    result = std::accumulate(data, data + count, 0);
}

int addNumbersForAsync(int* data, size_t count) {
    return std::accumulate(data, data + count, 0);
}

vector<thread> lunchSplitWorkersWithThreads(vector<int> &vec, vector<int> &results) {
	vector<thread> threads;
	size_t h = vec.size()/2;
	threads.emplace_back(addNumbersForThread, vec.data(), h, ref(results[0]));
	threads.emplace_back(addNumbersForThread, vec.data() + h, vec.size() - h, ref(results[1]));
	return threads;
}

vector<future<int>> lunchSplitWorkersWithAsync(vector<int> &vec) {
	vector<future<int>> futures;
	size_t h = vec.size()/2;
	futures.push_back(async(launch::async, addNumbersForAsync, vec.data(), h));
	futures.push_back(async(launch::async, addNumbersForAsync, vec.data() + h, vec.size() - h));
	return futures;
}

int main() {
	vector<int> vec{1, 2, 3, 4, 5};

	// First, we compare Thread and Async, when the entire computation is done by one thread/task.

	// Thread
	int threadResult = 0;
	thread workerTh(addNumbersForThread, vec.data(), vec.size(), ref(threadResult));
	workerTh.join();
	assert(threadResult == 15);

	// Async
	future<int> fut = async(launch::async, addNumbersForAsync, vec.data(), vec.size());
	assert(fut.get() == 15);
	
	
	
	// Second, let's see how threads compare to async when we split the task at hand in a different function,
	// and would like to wait for the result in another function

	// 2 Threads
	vector<int> results{0, 0};
	vector<thread> threads = lunchSplitWorkersWithThreads(vec, results);
	for (auto &th: threads)
		th.join();
	assert(results[0] + results[1] == 15);

	// 2 Async tasks
	vector<future<int>> futures = lunchSplitWorkersWithAsync(vec);
	assert(futures[0].get() + futures[1].get() == 15);
	
	return 0;
} 

