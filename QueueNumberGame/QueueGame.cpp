#include "library.h"

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

void DrawBox() {
	SHORT baseX = 5, baseY = 2;
	for (int i = baseX; i < MaxWidth - 4; i++) {
		RenderText((char*)"=", i, baseY, ColorCode_Green);
	}

	for (int i = baseX; i < MaxWidth - 4; i++) {
		RenderText((char*)"=", i, MaxHeight - 2, ColorCode_Green);
	}

	for (int j = baseY + 1; j < MaxHeight - 2; j++) {
		RenderText((char*)"||", baseX, j, ColorCode_Green);
	}

	for (int j = baseY + 1; j < MaxHeight - 2; j++) {
		RenderText((char*)"||", MaxWidth - 6, j, ColorCode_Green);
	}
}

void Login(char* name) {
	SHORT baseX = 5, baseY = 2;
	DrawBox();

	RenderText((char*)"Enter your name: ", baseX + 12, baseY + 13, 2);
	GotoXY(baseX + 13 + 17, baseY + 13);
	std::cin.get(name, 30, '\n');

}

void DrawName(char* name, SHORT X, SHORT Y) {
	SHORT baseX = X, baseY = Y;
	RenderText((char*)"Name: ", baseX, baseY, ColorCode_Cyan);
	RenderText(name, baseX + 6, baseY, ColorCode_Yellow);
}

void DrawMenu(str choice[], int numberOfChoice, int isChoosed, SHORT X, SHORT Y) {
	SHORT baseX = X, baseY = Y;
	for (SHORT index = 0; index < numberOfChoice; index++) {
		int x = baseX + (20 - strlen(choice[index])/2);
		if (index == isChoosed)
			RenderText((char*)choice[index], x, baseY + index, ColorCode_Green*16 + ColorCode_Black);
		else 
			RenderText((char*)choice[index], x, baseY + index, ColorCode_Green);
	}
}

void MainMenu(char* name) {
	clrscr();
	bool running = true;
	SHORT baseX = 7, baseY = 3;
	str choice[5]{ "Start Game", "High Score", "History", "Setting", "Quit Game" };
	int numberOfChoice = 5;
	while (running) {
		int isChoosed = 0;
		DrawBox();
		DrawName(name, baseX, baseY);
		DrawMenu(choice, numberOfChoice, isChoosed, baseX + 13, baseY + 8);
		running = 0;
	}
}

int main() {
	SetConsoleOutputCP(65001);
	SetWindowSize(MaxWidth, MaxHeight);
	char* name = new char[30];
	Login(name);
	MainMenu(name);
	
	return 0;
}