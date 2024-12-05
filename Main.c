#include "Declarations.h"
//#include <windows.h>
//#include <conio.h>
//#include "keys.h"
//#include "ConsoleControls.h"

int score = 0;
void drawBoardOnly(CHAR_INFO* mainchInfo, COORD coord, int rows, int cols) {   //TODO: cange the colors
	for (int j = 0; j < cols; j++) {
		mainchInfo[coord.X + j].Char.AsciiChar = 'W';
		mainchInfo[coord.X + j].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	}
	for (int i = 2; i <= rows - 1; i++) {
		mainchInfo[i * coord.X + 0].Char.AsciiChar = 'W';
		mainchInfo[i * coord.X + 0].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		for (int j = 1; j <= cols - 2; j++) {
			mainchInfo[i * coord.X + j].Char.AsciiChar = ' ';
			mainchInfo[i * coord.X + j].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		}
		mainchInfo[i * coord.X + cols - 1].Char.AsciiChar = 'W';
		mainchInfo[i * coord.X + cols - 1].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	}
	for (int j = 0; j < cols; j++) {
		mainchInfo[rows * coord.X + j].Char.AsciiChar = 'W';
		mainchInfo[rows * coord.X + j].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	}

	put_screen(&coord, mainchInfo);
}

void drawFruits(CHAR_INFO* mainchInfo, COORD coord, int rows, int cols, int Maze[25][45]) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (Maze[i][j] == 2) {
				mainchInfo[i * coord.X + j].Char.AsciiChar = '*';
				mainchInfo[i * coord.X + j].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
			}
		}
	}
	put_screen(&coord, mainchInfo);
}

void drawMaze(CHAR_INFO* mainchInfo, COORD coord, int rows, int cols, int Maze[25][45]) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (Maze[i][j] == 1) {
				mainchInfo[i * coord.X + j].Char.AsciiChar = 'W';
				mainchInfo[i * coord.X + j].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
			}
			if (Maze[i][j] == 2) {
				mainchInfo[i * coord.X + j].Char.AsciiChar = '*';
				mainchInfo[i * coord.X + j].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
			}
		}
	}
	put_screen(&coord, mainchInfo);
}

int GetKey()
{
	int ch;
	ch = _getch();
	if (ch == 0 || ch == 224) {
		ch = _getch();
		ch += 256;
	}
	return ch;
}

void drawSnake(CHAR_INFO* mainchInfo, COORD coord, struct Point* head) {
	struct Point* temp = head;
	mainchInfo[temp->y * coord.X + temp->x].Char.AsciiChar = '0';
	mainchInfo[temp->y * coord.X + temp->x].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	temp = temp->back;
	while (temp->back != NULL) {
		mainchInfo[temp->y * coord.X + temp->x].Char.AsciiChar = 'o';
		mainchInfo[temp->y * coord.X + temp->x].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		temp = temp->back;
	}
	mainchInfo[temp->y * coord.X + temp->x].Char.AsciiChar = ' ';
	//mainchInfo[temp->y * coord.X + temp->x].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	put_screen(&coord, mainchInfo);
}

int checkPosition(int x, int y, struct Point* head, struct Point* tail) {
	if (snakeBites(head))
		return 1;
	if (Maze[y][x] == 0)
		return 0;
	else if (Maze[y][x] == 1 || Maze[y][x] == 3)
		return 1;
	else if (Maze[y][x] == 2)
	{
		Maze[y][x] = 0;
		snakeGrow(tail);
		score += 1;
		return 0;
	}

}

int main() {
	int rows = 25, cols = 45;

	CHAR_INFO* mainchInfo;
	COORD coord = {0,0};
	mainchInfo = get_screen(&coord);
	set_cursor_visible(0);
	int KEY = KEY_UP;
	int gameOver = 0;

	//drawBoardOnly(mainchInfo, coord, rows, cols);
	//drawFruits(mainchInfo, coord, rows, cols, Maze)
	drawMaze(mainchInfo, coord, rows, cols, Maze);

	struct Point* Head;
	Head = (struct Point*)malloc(sizeof(struct Point));
	Head = snakeAwakening(Head, 22, 22);
	drawSnake(mainchInfo, coord, Head);
	struct Point* Tail;
	Tail = tailId(Head);


	while (!gameOver) {

		if (_kbhit())
		{
			KEY = GetKey();
		}
		switch (KEY)
		{
		case KEY_LEFT:
			xMinusOne(Tail);
			Sleep(90);
			break;
		case KEY_RIGHT:
			xPlusOne(Tail);
			Sleep(90);
			break;
		case KEY_UP:
			yMinusOne(Tail);
			Sleep(160);
			break;
		case KEY_DOWN:
			yPlusOne(Tail);
			Sleep(160);
			break;
		}
		gameOver = checkPosition(Head->x, Head->y, Head, Tail);
		Tail = tailId(Head);
		drawSnake(mainchInfo, coord, Head);
		if (score == 6) {
			clrScr();
			printf("You Win");
			return 0;
		}

	}

	clrScr();
	printf("You Lose");
	return 0;
}