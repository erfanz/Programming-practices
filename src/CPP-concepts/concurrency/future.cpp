#include <future>
#include <iostream>
#include <thread>

using namespace std;

int main() {
  // "async" function executes the task (here, the lambda function) asynchronously (potentially
  // in a separate thread which may be part of a thread pool), and returns a future object,
  // which will be filled once the task is finished. 
	future<void> myFuture = async(launch::async, [](){cout << "I'm a new thread" << endl;});
	future<int> myFuture2 = async(launch::async, [](){cout << "I'm yet another thread" << endl; return 42; });
	
	
	myFuture.get();
	int output = myFuture2.get();
	
	cout << output << endl;
	
	return 0;	
}
