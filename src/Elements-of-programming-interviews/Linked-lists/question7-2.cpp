/*
 * Given a reference to the head of singly linked list L,
 * determine whether L ends in a null or reaches a cycle of nodes.
 * Return NULL if there does not exist a cycle, and the reference to
 * the start of the cycle if a cycle is present
 */

#include "LinkedList.hpp"

/*
 * Time complexity:   O(N)
 * Memory complexity: O(1)
 */
ptrLL hasCycle(const ptrLL& head) {
	/*
	 * Idea: Have two pointers that walks the linked list, FAST and SLOW. the FAST pointer walks 2 nodes in each iteration,
	 * while the SLOW pointer walks 1 node. It is guaranteed that the two pointers will meet somewhere, iff the linked list
	 * has cycle
	 */

	ptrLL slow = head, fast = head;
	while (slow && slow->next_ && fast && fast->next_ && fast->next_){
		slow = slow->next_;
		fast = fast->next_->next_;

		if (slow == fast){
			// Now that we know there is a cycle, we first need to find the length of the cycle in order to find the head of
			// the cycle. To find the length of the cycle, we advance the SLOW pointer and see when it reaches the FAST pointer again.
			unsigned cycleLength = 0;
			do  {
				slow = slow->next_;
				cycleLength++;
			}while(slow != fast);

			// Now we advance the FAST pointer by the cycle's length, and then advance them one by one and see where they meet.
			fast = head, slow = head;
			for (unsigned i = 0; i < cycleLength; i++)
				fast = fast->next_;

			while (fast != slow){
				slow = slow->next_;
				fast = fast->next_;
			}
			return slow;
		}
	}

	return nullptr;
}
