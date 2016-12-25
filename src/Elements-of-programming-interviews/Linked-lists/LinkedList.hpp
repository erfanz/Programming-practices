/*
 * A minimal implementation of linked list.
 */

#include <memory>
#include <vector>
#include <iostream>

template <typename T>
class Node{
public:
	// these fields are made public for the sake of easier access in future functions. In reality, they must be definitely hidden.
	T data_;
	std::shared_ptr<Node<T> > next_;

	Node(const T& data, const std::shared_ptr<Node<T>> &next)
	: data_(data),
	  next_(next){
	}
};

template <typename T>
class LinkedList{
public:
	std::shared_ptr<Node<T>> head;

	LinkedList(){
		head = nullptr;
	}

	void insertInBeginning(const T &data){
		std::shared_ptr<Node<T>> node(new Node<T>(data, head));
		head = node;
	}

	void printList(){
		std::shared_ptr<Node<T>> current = head;
		std::cout << "list: ";
		while (current) {
			std::cout << current->data_ << " --> ";
			current = current->next_;
		}

		std::cout << "null" << std::endl;

	}

	// methods
	static std::shared_ptr<LinkedList<T>> makeList(const std::vector<T> &inputVector){
		std::shared_ptr<LinkedList<T>> list(new LinkedList<T>());

		for (int i = inputVector.size() - 1; i>= 0; i--){
			list->insertInBeginning(inputVector[i]);
		}
		return list;
	}
};


typedef Node<int> LL_int;
typedef std::shared_ptr<LL_int> ptrLL;

