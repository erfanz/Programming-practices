/*
 * main.cpp
 *
 *  Created on: Dec 31, 2016
 *      Author: Erfan Zamanian (erfanz@cs.brown.edu)
 */

#include <iostream>
#include <boost/coroutine/all.hpp>
#include <string>
#include <functional>

using namespace boost::coroutines;

void printUpTo10(coroutine<void>::push_type &sink){
	int iteration_ = 1;
	while (iteration_ <= 10) {
		std::cout << iteration_ << " " ;
		sink();
		iteration_++;
	}
}

void printFromM_To_N(coroutine<void>::push_type &sink, int lowerLimit, int upperLimit){
	int iteration_ = lowerLimit;
	while (iteration_ <= upperLimit) {
		std::cout << iteration_ << " " ;
		sink();
		iteration_++;
	}
}

void generateOddNumbersUpToN(coroutine<int>::push_type &sink, int upperLimit){
	int num = 1;
	while (num <= upperLimit) {
		if (num % 2 == 1)
			sink(num);
		++num;
	}
}

void printPair(coroutine<std::pair<int, std::string>>::pull_type &source){
	int receivedPair = 0;
	for (std::pair<int, std::string> &p: source)
		std::cout << "pair #" << ++receivedPair << ": " << p.first << ", " << p.second << std::endl;
}

class S{
public:
	void func(){
		;
	}
};

int main() {
	std::cout << "caller: pull_type, callee: push_type, with no input argument or return value" << std::endl;
	coroutine<void>::pull_type mySource1{printUpTo10};
	while (mySource1())
		;
	std::cout << std::endl << std::endl;

	std::cout << "caller: pull_type, callee: push_type, with 2 input arguments and no return value" << std::endl;
	using std::placeholders::_1;
	int m = 5;
	int n = 15;
	coroutine<void>::pull_type mySource2{std::bind(printFromM_To_N, _1, m, n)};
	while (mySource2())
		;
	std::cout << std::endl << std::endl;


	std::cout << "caller: pull_type, callee: push_type, with 2 input arguments and return value" << std::endl;
	using std::placeholders::_1;
	n = 20;
	coroutine<int>::pull_type mySource3{std::bind(generateOddNumbersUpToN, _1, n)};
	for (auto &i: mySource3)
		std::cout << i << " ";
	std::cout << std::endl << std::endl;


	std::cout << "caller: push_type, callee: pull_type, with 2 input arguments" << std::endl;
	coroutine<std::pair<int, std::string>>::push_type mySink{printPair};
	mySink(std::make_pair(12, "first string"));
	mySink(std::make_pair(19, "second string"));
}


