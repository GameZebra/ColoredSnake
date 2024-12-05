#pragma once
struct Point {
	struct Point* front;
	int x;
	int y;
	struct Point* back;
};
//void drawSnake(CHAR_INFO* mainchInfo, COORD coord, struct Point* head);
struct Point* snakeEating(int x, int y, struct Point* head);
struct Point* snakeAwakening(struct Point* head, int startX, int startY);
void xPlusOne(struct Point* tail);
void yPlusOne(struct Point* tail);
void xMinusOne(struct Point* tail);
void yMinusOne(struct Point* tail);
struct Point* tailId(struct Point* head);
int snakeBites(struct Point* head);