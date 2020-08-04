/*
 * coroutine_with_class.cpp
 *
 *  Created on: Jan 1, 2017
 *      Author: Erfan Zamanian (erfanz@cs.brown.edu)
 */

#include <iostream>
#include <vector>
#include <boost/coroutine/all.hpp>

using namespace boost::coroutines;

class Worker {
private:
	int id_;
	int iteration_;
public:
	Worker(int id): id_(id), iteration_(0){};
	void printNextIteration(coroutine<void>::push_type &sink){
		while (true) {
			std::cout << "Worker " << id_ << ": iteration #" << iteration_ << std::endl;
			sink();
			++iteration_;
		}
	}
};


int main() {
	// using a class's member function as the co-routine
	std::vector<Worker> workers;
	workers.emplace_back(0);
	workers.emplace_back(1);
	coroutine<void>::pull_type source0{std::bind(&Worker::printNextIteration, &workers[0], std::placeholders::_1)};
	coroutine<void>::pull_type source1{std::bind(&Worker::printNextIteration, &workers[1], std::placeholders::_1)};
	source0();
	source1();


	// late initialization of a pull_type
	Worker w(2);
	coroutine<void>::pull_type *source3;
	source3 = new coroutine<void>::pull_type(std::bind(&Worker::printNextIteration, &w, std::placeholders::_1));
	(*source3)();
}
