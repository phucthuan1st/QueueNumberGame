#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
typedef const char* str;

#define BOUND 52

struct Node {
	Node* next;
	int value;

	Node(int value) 
	{
		this->next = NULL;
		this->value = value;
	}

};

struct Queue {
	Node* front;
	Node* rear;

	void Initialize() {
		front = NULL;
		rear = NULL;
	}

	int size() {
		if (front == NULL)
			return 0;
		int size = 0;
		Node* pCur = front;
		while (pCur != rear) {
			size++;
			pCur = pCur->next;
		}
		return size + 1;
	}

	void push(Node* node) {
		if (size() == 0) {
			front = rear = node;
		}
		else {
			rear->next = node;
			rear = node;
		}
	}

	int peek() {
		return front->value;
	}

	void pop() {
		Node* old_front = front;
		front = front->next;
		delete old_front;
	}

	void display() {
		int index = 1;
		for (Node* p = front; p != NULL; p = p->next) {
			std::cout << p->value << " ";
			if (index == 10) {
				std::cout << "\n";
				index = 0;
			}
			index++;
		}
	}

	bool isExist(int value) {
		if (size() == 0)
			return false;
		for (Node* p = front; p != rear->next; p = p->next) {
			if (p->value == value)
				return true;
		}
		return false;
	}

};

typedef struct NPC {
	str name[16] {
		"Alexa",
		"Barbie",
		"Mariposa",
		"Texna",
		"Robert",
		"Geogre",
		"Jane",
		"Cinderella",
		"Belle",
		"Aurora",
		"Ariel",
		"Vie",
		"Jack",
		"Mary",
		"Taylor",
		"Samuel"
	};
} NPC_Name;

