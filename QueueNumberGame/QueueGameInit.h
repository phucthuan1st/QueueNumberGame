#pragma once
#include <iostream>
#include <fstream>
#include <ctime>

typedef const char* str;

#define BOUND 52

struct Node {
	Node* next;
	INT64 value;

	Node(INT64 value) 
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

	INT64 size() {
		if (front == NULL)
			return 0;
		INT64 size = 0;
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

	INT64 peek() {
		return front->value;
	}

	void pop() {
		Node* old_front = front;
		front = front->next;
		delete old_front;
	}

	void display() {
		INT64 index = 1;
		for (Node* p = front; p != NULL; p = p->next) {
			std::cout << p->value << " ";
			if (index == 10) {
				std::cout << "\n";
				index = 0;
			}
			index++;
		}
	}

	bool isExist(INT64 value) {
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
		"Sun",
		"Texna",
		"Robert",
		"Ong Noi",
		"Jane",
		"Cinderella",
		"Bo khung",
		"Aurora",
		"Ariel",
		"Vie",
		"Jack",
		"Ba Noi",
		"Tin",
		"Samuel"
	};
} NPC_Name;

struct Player {
	char* name;
	INT64 point;
};

struct Element {
	Player player;
	Element* next;

	Element(Player player) {
		this->player = player;
		this->next = NULL;
	}

};

struct HighScorePlayerList {
	Element* first_person;
	Element* last_person;

	void initialize() {
		first_person = last_person = NULL;
	}

	bool isEmpty() {
		if (first_person == NULL)
			return true;
		return false;
	}

	void push(Element* element) {
		if (isEmpty()) {
			first_person = last_person = element;
		}
		else {
			if (first_person->player.point <= element->player.point) {
				element->next = first_person;
				first_person = element;
			}
			else if (last_person->player.point >= element->player.point) {
				last_person->next = element;
				last_person = element;
			}
			else {
				for (Element* curElem = first_person; curElem->next != NULL; curElem = curElem->next) {
					if (curElem->player.point >= element->player.point && curElem->next->player.point <= element->player.point) {
						Element* front = curElem, * behind = curElem->next;
						element->next = behind;
						front->next = element;
						break;
					}
				}
			}
		}
	}

};
