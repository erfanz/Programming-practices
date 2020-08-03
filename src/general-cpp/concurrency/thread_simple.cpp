#include <thread>
#include <iostream>
#include <vector> 

void hello() {
	std::cout << "Hello World! " << std::this_thread::get_id() << std::endl;
}

void main_simple_threads() {
	std::vector<std::thread> threads;
	for (int i = 0; i < 5; i++)
		threads.push_back(std::thread(hello));
	
	for (int i = 0; i < 5; i++)
		threads[i].join();
}

void main_lambda() {
	std::vector<std::thread> threads;
	for (int i = 0; i < 5; i++)
		threads.push_back(std::thread(
			[](){std::cout << "Hello World! " << std::this_thread::get_id() << std::endl;}
			));
	
	for (int i = 0; i < 5; i++)
		threads[i].join();
}

int main() {
	std::cout << "Running threads with simple functions:" << std::endl;
	main_simple_threads();	
	
	std::cout << std::endl;
	std::cout << "Running threads with lambda:" << std::endl;
	main_lambda();	
	
	return 0;
}
