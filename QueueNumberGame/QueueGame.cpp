#include "library.h"

void FormatConsole() {
	SetConsoleTitle(TEXT("Queue Number Game"));
	SetWindowSize(MaxWidth, MaxHeight);
	SetScreenBufferSize(MaxWidth, MaxHeight);
	DisableCtrButton(0, 1, 1);
	DisableSelection();
	DisableResizeWindow();
	ShowScrollbar(0);
}

int random(int minN, int maxN) {
	return minN + rand() % (maxN + 1 - minN);
}

enum class KEY {UP, DOWN, LEFT, RIGHT, ENTER, ESCAPE, keynone};

KEY key(int _key_)
{
	if (_key_ == 224)
	{
		char c = _getch();
		if (c == 72)
			return KEY::UP;
		if (c == 80)
			return KEY::DOWN;
		if (c == 75)
			return KEY::LEFT;
		if (c == 77)
			return KEY::RIGHT;
	}
	else if (_key_ == 13)
		return KEY::ENTER;
	else if (_key_ == 27)
		return KEY::ESCAPE;
	return KEY::keynone;
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
			RenderText((char*)choice[index], x, baseY + index*2, ColorCode_Green*16 + ColorCode_Black);
		else 
			RenderText((char*)choice[index], x, baseY + index*2, ColorCode_Green);
	}
}

void MainMenu(char* name) {
	clrscr();
	FormatConsole();
	ShowCur(0);
	PlaySound(TEXT("./Resource/Main Menu Bg sound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	bool running = true;
	SHORT baseX = 7, baseY = 3;
	str choice[5]{ "  Start Game  ", "  High Score  ", "  History  ", "  Setting  ", "  Quit Game  " };
	int numberOfChoice = 5;
	int isChoosed = 0;
	DrawBox();
	DrawName(name, baseX, baseY);
	DrawMenu(choice, numberOfChoice, isChoosed, baseX + 13, baseY + 8);
	RenderText((char*)"Now playing: Origin - TheFatRat", baseX - 2, baseY + 26, ColorCode_Yellow);
	while (running) {
		
		int z = _getch();
		KEY stt = key(z);
		if (stt == KEY::UP) {
			if (isChoosed == 0)
				isChoosed = numberOfChoice - 1;
			else isChoosed--;
		}
		else if (stt == KEY::DOWN) {
			if (isChoosed == numberOfChoice - 1) {
				isChoosed = 0;
			}
			else
				isChoosed++;
		}
		else if (stt == KEY::ESCAPE) {
			exit(0);
		}
		DrawBox();
		DrawName(name, baseX, baseY);
		DrawMenu(choice, numberOfChoice, isChoosed, baseX + 13, baseY + 8);
	}
}

int main() {
	FormatConsole();
	char* name = new char[30];
	Login(name);
	MainMenu(name);
	
	return 0;
}