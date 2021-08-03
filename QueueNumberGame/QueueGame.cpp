#include "QueueGameInit.h"

int random(int minN, int maxN) {
	return minN + rand() % (maxN + 1 - minN);
}

void CreateANewQueue(Queue& q) {
	while (q.size() != 0) {
		q.pop();
	}

	srand(time(NULL)); //get new random seed

	while (q.size() != BOUND) {
		int number = random(0, 51);
		while (q.isExist(number))
			number = random(0, 51);
		Node* node = new Node(number);
		q.push(node);
	}
}

int main() {
	Queue q;
	q.Initialize();
	CreateANewQueue(q);
	q.display();
	return 0;
}