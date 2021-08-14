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

INT64 random(INT64 minN, INT64 maxN) {
	return minN + rand() % (maxN + 1 - minN);
}

enum class KEY {UP, DOWN, LEFT, RIGHT, ENTER, ESCAPE, keynone};

KEY key(INT64 _key_)
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
		INT64 number = random(0, 51);
		while (q.isExist(number))
			number = random(0, 51);
		Node* node = new Node(number);
		q.push(node);
	}
}

void DrawBox() {
	INT64 baseX = 5, baseY = 2;
	for (INT64 i = baseX; i < MaxWidth - 4; i++) {
		RenderText((char*)"=", i, baseY, ColorCode_Green);
	}

	for (INT64 i = baseX; i < MaxWidth - 4; i++) {
		RenderText((char*)"=", i, MaxHeight - 2, ColorCode_Green);
	}

	for (INT64 j = baseY + 1; j < MaxHeight - 2; j++) {
		RenderText((char*)"||", baseX, j, ColorCode_Green);
	}

	for (INT64 j = baseY + 1; j < MaxHeight - 2; j++) {
		RenderText((char*)"||", MaxWidth - 6, j, ColorCode_Green);
	}
}

void Login(char* name) {
	INT64 baseX = 5, baseY = 2;
	DrawBox();

	RenderText((char*)"Enter your name: ", baseX + 12, baseY + 13, 2);
	GotoXY(baseX + 13 + 17, baseY + 13);
	std::cin.get(name, 30, '\n');

}

void DrawName(char* name, INT64 X, INT64 Y) {
	INT64 baseX = X, baseY = Y;
	RenderText((char*)"Name: ", baseX, baseY, ColorCode_Cyan);
	RenderText(name, baseX + 6, baseY, ColorCode_Yellow);
	RenderText((char*)"Now playing: Origin - TheFatRat", baseX - 2, baseY + 26, ColorCode_Yellow);
}

void DrawMenu(str choice[], INT64 numberOfChoice, INT64 isChoosed, INT64 X, INT64 Y) {
	INT64 baseX = X, baseY = Y;
	for (INT64 index = 0; index < numberOfChoice; index++) {
		INT64 x = baseX + (20 - strlen(choice[index])/2);
		if (index == isChoosed)
			RenderText((char*)choice[index], x, baseY + index*2, ColorCode_Green*16 + ColorCode_Black);
		else 
			RenderText((char*)choice[index], x, baseY + index*2, ColorCode_Green);
	}
}

INT64 Choose(str process[], INT64 numProcess, INT64 &isChoosed, char* name) {
	INT64 baseX = 7, baseY = 3;
	INT64 running = 1;
	while (running) {
		DrawBox();
		DrawName(name, baseX, baseY);
		DrawMenu(process, numProcess, isChoosed, baseX + 13, baseY + 6);
		INT64 z = _getch();
		KEY stt = key(z);
		if (stt == KEY::UP) {
			if (isChoosed == 0)
				isChoosed = numProcess - 1;
			else isChoosed--;
		}
		else if (stt == KEY::DOWN) {
			if (isChoosed == numProcess - 1) {
				isChoosed = 0;
			}
			else
				isChoosed++;
		}
		else if (stt == KEY::ESCAPE) {
			clrscr();
			isChoosed = -1;
			return -1;
		}
		else if (stt == KEY::ENTER) {
			clrscr();
			return isChoosed;
		}
	}
	return -1;
}

INT64 gameMode(char* name) {
	clrscr();
	INT64 baseX = 7, baseY = 3;
	str mode[8] = {"  player vs 2 bot  ",
				   "  player vs 4 bot  ",
				   "  player vs 6 bot  ",
				   "  player vs 8 bot  ",
				   "  player vs 10 bot  ",
				   "  player vs 12 bot  ",
				   "  player vs 14 bot  ",
				   "  player vs 16 bot  "};
	INT64 numberOfMode = 8;
	INT64 isChoosed = 0;
	INT64 running = 1;
	return Choose(mode, numberOfMode, isChoosed, name);
}

void Game(char* name, INT64 gamemode) {
	INT64 numberofplayer = 2*(gamemode + 1) + 1;
	NPC_Name npc;
	Player* player = new Player[numberofplayer];
	for (int i = 0; i < numberofplayer; i++) {
		player[i].name = new char[30];
		player[i].point = 0;
	}
	for (int i = 0; i < numberofplayer - 1; i++) {
		strcpy_s(player[i + 1].name, 30, npc.name[i]);
	}
	strcpy_s(player[0].name, 30, name);
	Queue queue;
	queue.Initialize();
	CreateANewQueue(queue);
	INT64 baseX = 7, baseY = 3;
	clrscr();
	DrawBox();
	DrawName(name, baseX, baseY);
	PlaySound(TEXT("./Resource/xskt.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	for (int i = 0; i < numberofplayer; i++) {
		SHORT X = baseX + 3, Y = baseY + 3 + 17 / numberofplayer * i;
		RenderText(player[i].name, X, Y, ColorCode_Yellow);
		RenderText((char*)"|", X + 11, Y, ColorCode_Cyan); //18, 26, 34
		RenderText((char*)"|", X + 22, Y, ColorCode_Cyan);
		RenderText((char*)"|", X + 30, Y, ColorCode_Cyan);
	}
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < numberofplayer; i++) {
			GotoXY(baseX + 3 + 18 + 8 * j, baseY + 3 + 17 / numberofplayer * i);
			TextColor(ColorCode_Red);
			std::cout << queue.peek();
			queue.pop();
		}
	}
	INT64 z = _getch();
}

void HighScore() {
	
}
void History() {
	
}
void Setting() {
	
}

void MainMenu(char* name) {
	clrscr();
	FormatConsole();
	ShowCur(0);
	PlaySound(TEXT("./Resource/Main Menu Bg sound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	bool running = true;
	INT64 baseX = 7, baseY = 3;
	str choice[5]{ "  Start Game  ", "  High Score  ", "  History  ", "  Setting  ", "  Quit Game  " };
	INT64 numberOfChoice = 5;
	RenderText((char*)"Now playing: Origin - TheFatRat", baseX - 2, baseY + 26, ColorCode_Yellow);
	while (running) {
		clrscr();
		INT64 isChoosed = 0;
		Choose(choice, 5, isChoosed, name);
		if (isChoosed == 0) {
			INT64 gamemode = gameMode(name);
			if (gamemode != -1) {
				Game(name, gamemode);
				PlaySound(TEXT("./Resource/Main Menu Bg sound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
		}
		else if (isChoosed == 1)
			HighScore();
		else if (isChoosed == 2)
			History();
		else if (isChoosed == 3)
			Setting();
		else if (isChoosed == 4)
			running = 0;
	}
		
}

int main() {
	FormatConsole();
	char* name = new char[30];
	Login(name);
	MainMenu(name);
	
	return 0;
}