/*
 * Find the median in a sorted circular singly linked list
 */

#include "LinkedList.hpp"
#include <cmath>	// math.floor

typedef LinkedList<int> LL;
typedef std::shared_ptr<LL> ptrLL;

// Time Complexity:   O(N)
// Memory Complexity: O(1)
double findMedian(ptrLL node) {
	ptrLL minimumNode = node;
	ptrLL currentP = node;
	int size = 0;
	do {
		++size;
		currentP = currentP->next_;
		if (currentP->data < minimumNode->data)
			minimumNode = currentP;
	}while (currentP != node);

	// starting from the minimum node, walk n/2 nodes to find the median, where n is the number of nodes
	int half = (size % 2 == 0 ?  floor(size / 2) - 1 : floor(size / 2));
	for (unsigned i = 0; i < half; i++)
		minimumNode = minimumNode->next_;

	if (size % 2 == 0)
		return ((double)(minimumNode->data + minimumNode->data)) / 2;
	else
		return minimumNode->data;
}



// Points:
// 1- When finding the median, be careful if the number of elements is odd or even.
//    If they are even, the median should be the average of the two middle elements.




