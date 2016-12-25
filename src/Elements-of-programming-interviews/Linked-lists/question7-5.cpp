/*
 * question7-5.cpp
 *
 *  Created on: Dec 15, 2016
 *      Author: Erfan Zamanian (erfanz@cs.brown.edu)
 */

// n0 n1 n2 n3 n4 n5 n6
// n0 n2 n4 n6 n1 n3 n5
// n0 n2 n1 n3
void evenOddList(ptrLL &originalList){
	LinkedList& evenEnd = originalList;
	LinkedList& oddEnd  = originalList;
	ptrLL current = originalList;

	unsigned index = 1;
	while (current != nullptr){
		if (index % 2 == 0){
			// even
			evenEnd->next_ = current;

		}
		else {
			oddEnd->next_ =
			oddEnd = current;
		}
	}


}



