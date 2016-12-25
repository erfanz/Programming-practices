/*
 * Zipping a list:
 * Given a List L = <l_0, l_1, l_2, ..., l_(n-1)>, write a function that
 * returns a new list representing zip(L), i.e. L_zip = <l_0, l_(n-1), l_1, l_(n-2), ....>
 */

#include "LinkedList.hpp"

template <typename T> std::shared_ptr<Node<T> > findMiddle(const std::shared_ptr<Node<T>> &list);
template <typename T> std::shared_ptr<Node<T>> makeReverse(std::shared_ptr<Node<T>> &list);
template <typename T> void connect_a_to_b_and_advance_a(std::shared_ptr<Node<T>> &a, const std::shared_ptr<Node<T>> &b);


/*
 * Time complexity:   O(N)
 * Memory complexity: O(1)
 * Corner cases:
 */
template <typename T>
std::shared_ptr<Node<T> > zipMaker(const std::shared_ptr<Node<T>> &head){
	// corner case 1 & 2: list with 0 or 1 node
	if (!head || !head->next_) return head;

	// find the middle of the list
	std::shared_ptr<Node<T> > middle = findMiddle(head);

	// reverse the linked list from the middle node to the end (i.e. -> -> -> -> mid <- <- <- <-)
	std::shared_ptr<Node<T>> reversedList = makeReverse(middle);

	while (head && reversedList){
		// connect list->next to reversedList, and advanced list to its current next
		connect_a_to_b_and_advance_a(head, reversedList);
		if (reversedList)
			// connect reversedList->next to list, and advanced reversedList to its current next
			connect_a_to_b_and_advance_a(reversedList, head);
	}
}


/* finds the middle element */
template <typename T>
std::shared_ptr<Node<T> > findMiddle(const std::shared_ptr<Node<T>> &node){
	size_t i = 0, length = 0;
	std::shared_ptr<Node<T> > current = node;
	while (current){
		++length;
		current = current->next_;
	}
	current = node;
	while (i < length/2){
		++i;
		current = current->next_;
	}
	return current;
}

/* Reverses the list (i.e. turns -> -> -> -> into <- <- <- <-), and returns the head to the new list */
template <typename T>
std::shared_ptr<Node<T>> makeReverse(std::shared_ptr<Node<T>> &node){
	// corner case 1 & 2: list with 0 or 1 node
	if (!node || !node->next_) return node;

	std::shared_ptr<Node<T>> pre = nullptr, current, next = node;
	do{
		current = next;
		next = current->next_;
		current->next_ = pre;
	} while(next);

	return current;
}

/* connects a-> to b, and advances a to its current next */
template <typename T>
void connect_a_to_b_and_advance_a(std::shared_ptr<Node<T>> &a, const std::shared_ptr<Node<T>> &b){
	std::shared_ptr<Node<T>> temp = a->next_;
	a->next_ = b;
	a = temp;
}

int main() {
	std::vector<int> elements = {1,2,3,4,5,6};
	std::shared_ptr<LinkedList<int>> list = LinkedList<int>::makeList(elements);
	list->printList();
	std::cout << findMiddle<int>(list->head)->data_ << std::endl;
	std::cout << zipMaker<int>(list->head)->data_ << std::endl;

}

