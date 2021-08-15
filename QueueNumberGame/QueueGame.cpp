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

void DrawTutorial() {
	int baseX = 0, baseY = 0;
	RenderText((char*)"Use arrow key to navigate between option, Enter to select, ESC to back.", baseX + 5, MaxHeight, ColorCode_White);
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


	DrawTutorial();
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

void saveHighScore(Player player) {
	//save player high score
	std::fstream fin("./Data/HighScore.dat", std::ios::in);
	HighScorePlayerList list;
	list.initialize();
	for (int i = 0; i < 10; i++) {
		Player dump;
		dump.name = new char[30];
		fin >> dump.point;
		fin.getline(dump.name, 30);
		int n = strlen(dump.name);
		for (int j = 0; j < n; j++) {
			dump.name[j] = dump.name[j + 1];
		}
		dump.name[n] = '\0';
		Element* ele = new Element(dump);
		list.push(ele);
	}
	Element* me = new Element(player);
	list.push(me);
	fin.close();
	std::fstream fout("./Data/HighScore.dat", std::ios::out);
	Element* cur = list.first_person;
	for (int i = 0; i < 10; i++) {
		fout << cur->player.point << " " << cur->player.name << "\n";
		cur = cur->next;
	}
	fout.close();
}

void rank(Player* &player, int numberofplayer) {

	INT64 baseX = 7, baseY = 3;
	for (int j = baseY + 2; j < MaxHeight - 7; j++) {
		for (int i = baseX; i < MaxWidth - 6; i++) {
			RenderText((char*)" ", i, j, ColorCode_Black);
		}
	}

	for (int i = 0; i < numberofplayer - 1; i++) {
		for (int j = i; j < numberofplayer; j++) {
			if (player[i].point < player[j].point) {
				Player dummy = player[i];
				player[i] = player[j];
				player[j] = dummy;
			}
		}
	}

	RenderText((char*)"  RANKING  ", baseX + 20, baseY + 1, ColorCode_White);
	
	for (int i = 0; i < numberofplayer; i++) {
		INT64 X = baseX + 10, Y = baseY + 3 + 17/numberofplayer*i;
		GotoXY(X, Y);
		TextColor(ColorCode_Yellow);
		std::cout << i + 1 << ". ";
		GotoXY(X + 4, Y);
		TextColor(ColorCode_Cyan);
		std::cout << player[i].name;
		GotoXY(X + 25, Y);
		TextColor(ColorCode_Red);
		std::cout << player[i].point;
	}
}

void saveHistory(Player player) {
	std::string filename = player.name;
	std::fstream fout("./Data/" + filename + ".dat", std::ios::out | std::ios::app);
	time_t now = time(0);
	tm* gmtm = gmtime(&now);
	char* dt = asctime(gmtm);
	fout << player.name << ",Score: " << player.point << ",Date: " << dt;
	fout.close();
}

void Game(char* name, INT64 gamemode) {

	//initialize game statictis
		
		//gamemode
	INT64 numberofplayer = 2*(gamemode + 1) + 1;
	NPC_Name npc;

		//player statictis
	Player* player = new Player[numberofplayer];
	for (int i = 0; i < numberofplayer; i++) {
		player[i].name = new char[30];
		player[i].point = 0;
	}
	for (int i = 0; i < numberofplayer - 1; i++) {
		strcpy_s(player[i + 1].name, 30, npc.name[i]);
	}
	strcpy_s(player[0].name, 30, name);

		//GUI
	INT64 baseX = 7, baseY = 3;
	clrscr();
	DrawBox();
	DrawName(name, baseX, baseY);
	Player winner;
	winner.name = new char[30];
	winner.point = 0;
	for (int i = 0; i < numberofplayer; i++) {
		SHORT X = baseX + 3, Y = baseY + 3 + 17 / numberofplayer * i;
		RenderText(player[i].name, X, Y, ColorCode_Yellow);
		RenderText((char*)" | ", X + 14, Y, ColorCode_Cyan); //18, 26, 34
		RenderText((char*)" | ", X + 22, Y, ColorCode_Cyan);
		RenderText((char*)" | ", X + 30, Y, ColorCode_Cyan);
		RenderText((char*)" | ", X + 38, Y, ColorCode_Yellow);
	}
	RenderText((char*)"Phase 1", baseX + 19, baseY + 2, ColorCode_Yellow);
	RenderText((char*)"Phase 2", baseX + 27, baseY + 2, ColorCode_Yellow);
	RenderText((char*)"Phase 3", baseX + 35, baseY + 2, ColorCode_Yellow);
	RenderText((char*)"Total Point", baseX + 43, baseY + 2, ColorCode_Pink);

		//number queue
	Queue queue;
	queue.Initialize();
	CreateANewQueue(queue);

		//music
	if (MusicOn) {
		PlaySound(TEXT("./Resource/xskt.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		RenderText((char*)"Now playing: Xo So Kien Thiet - DYX Remix                ", baseX - 2, baseY + 26, ColorCode_Yellow);
	}
	else {
		PlaySound(NULL, 0, 0);
		RenderText((char*)"                                                 ", baseX - 2, baseY + 26, ColorCode_Yellow);
	}

		//gameplay
	for (int j = 0; j < 4; j++) {
		if (j < 3)
			for (int i = 0; i < numberofplayer; i++) {
				GotoXY(baseX + 3 + 18 + 8 * j, baseY + 3 + 17 / numberofplayer * i);
				TextColor(ColorCode_Red);
				INT64 point = queue.peek();
				std::cout << point;
				player[i].point += point;
				if (winner.point < player[i].point) {
					winner = player[i];
				}
				Sleep(200);
				queue.pop();
			}
		else
			for (int i = 0; i < numberofplayer; i++) {
				GotoXY(baseX + 3 + 18 + 8 * j, baseY + 3 + 17 / numberofplayer * i);
				TextColor(ColorCode_White);
				std::cout << player[i].point;
				Sleep(100);
			}
	}

		//Announce the winner's name
	RenderText((char*)"The Winner is: ", baseX + 3, baseY + 23, ColorCode_Cyan);
	GotoXY(baseX + 18, baseY + 23);
	TextColor(ColorCode_Yellow);
	std::cout << winner.point << " points - " << winner.name;
	
	saveHighScore(player[0]);
	saveHistory(player[0]);

	RenderText((char*)"Press any key to see ranking", baseX + 18, baseY + 24, ColorCode_Red);
	INT64 z = _getch();
	RenderText((char*)"Press any key to see ranking", baseX + 18, baseY + 24, ColorCode_Black);

	rank(player, numberofplayer);

	z = _getch();

}

void HighScore(char* name) {

	INT64 baseX = 7, baseY = 3;
	clrscr();
	DrawBox();
	DrawName(name, baseX, baseY);
	RenderText((char*)"HIGH SCORE", baseX + 15, baseY + 2, ColorCode_DarkCyan);
	std::fstream fin("./Data/HighScore.dat", std::ios::in);
	
	for (int i = 0; i < 10; i++) {
		Player dump;
		dump.name = new char[30];
		fin >> dump.point;
		fin.getline(dump.name, 30);
		int n = strlen(dump.name);
		for (int j = 0; j < n; j++) {
			dump.name[j] = dump.name[j + 1];
		}
		dump.name[n] = '\0';
		GotoXY(baseX + 5, baseY + 4 + i * 2);
		TextColor(ColorCode_Yellow);
		std::cout << i + 1;
		TextColor(ColorCode_Cyan);
		std::cout << ". " << dump.name;
		GotoXY(baseX + 35, baseY + 4 + i * 2);
		TextColor(ColorCode_Red);
		std::cout << dump.point;
	}

	fin.close();
	int z = _getch();
}

void History(char* name) {
	std::string filename = name;
	std::fstream fin("./Data/" + filename + ".dat", std::ios::in);

	INT64 baseX = 7, baseY = 3;
	clrscr();
	DrawBox();
	DrawName(name, baseX, baseY);
	RenderText((char*)"YOUR HISTORY", baseX + 25, baseY + 2, ColorCode_DarkCyan);
	int i = 0;
	if (!fin.is_open()) {
		RenderText((char*)"Your history is empty, you never play any match", baseX + 10, baseY + 4, ColorCode_Yellow);
	}
	else
		while (!fin.eof()) {
			char* buffer = new char[50];
			fin.getline(buffer, 50, '\n' | '\0');
			if (strcmp(buffer, "") == 0)
				break;
			char* playername = strtok(buffer, ",");
			RenderText(playername, baseX + 3, baseY + i + 3, ColorCode_Yellow);
			char* point = strtok(NULL, ",");
			RenderText(point, baseX + 20, baseY + i + 3, ColorCode_Cyan);
			char* date = strtok(NULL, ",");
			RenderText(date, baseX + 33, baseY + i + 3, ColorCode_Green);
			i++;
		}
	fin.close();
	int z = _getch();
	
}

void Setting(char* name) {
	INT64 baseX = 7, baseY = 3;
	clrscr();
	DrawBox();
	DrawName(name, baseX, baseY);
	RenderText((char*)"SETTING", baseX + 25, baseY + 2, ColorCode_DarkCyan);
	
	RenderText((char*)"Music:", baseX + 15, baseY + 10, ColorCode_Yellow);
	while (true) {
		if (MusicOn)
			RenderText((char*)" <   On   >", baseX + 30, baseY + 10, ColorCode_Cyan);
		else
			RenderText((char*)" <   Off  >", baseX + 30, baseY + 10, ColorCode_Red);
		int z = _getch();
		KEY _key = key(z);
		if (_key == KEY::LEFT || _key == KEY::RIGHT)
			MusicOn = !MusicOn;
		else if (_key == KEY::ENTER || _key == KEY::ESCAPE)
			return;
	}


}

void MainMenu(char* name) {
	ShowCur(0);

	INT64 baseX = 7, baseY = 3;

	//main menu options
	str choice[5]{ "  Start Game  ", "  High Score  ", "  History  ", "  Setting  ", "  Quit Game  " };
	INT64 numberOfChoice = 5;
	
	bool running = true;
	while (running) {
		clrscr();

		if (MusicOn) {
			PlaySound(TEXT("./Resource/Main Menu Bg sound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			RenderText((char*)"Now playing: Origin - TheFatRat                  ", baseX - 2, baseY + 26, ColorCode_Yellow);
		}
		else {
			PlaySound(NULL, 0, 0);
			RenderText((char*)"                                                 ", baseX - 2, baseY + 26, ColorCode_Yellow);
		}
		INT64 isChoosed = 0;
		Choose(choice, 5, isChoosed, name);

		if (isChoosed == 0) {
			INT64 gamemode = gameMode(name);
			if (gamemode != -1) {
				Game(name, gamemode);
			}
		}
		else if (isChoosed == 1)
			HighScore(name);
		else if (isChoosed == 2)
			History(name);
		else if (isChoosed == 3)
			Setting(name);
		else if (isChoosed == 4)
			running = false;
	}
		
}

int main() {
	
	FormatConsole();
	char* name = new char[30];
	Login(name);
	MainMenu(name);
	
	return 0;
}