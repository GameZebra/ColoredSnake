#include "snake.h"
#include<stdio.h>
#include<windows.h>

//void drawSnake(CHAR_INFO* mainchInfo, COORD coord, struct Point* head) {
//	struct Point* temp = head;
//	mainchInfo[temp->y * coord.X + temp->x].Char.AsciiChar = '8';
//	mainchInfo[temp->y * coord.X + temp->x].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//	temp = temp->back;
//	while (temp->back != NULL) {
//		mainchInfo[temp->y * coord.X + temp->x].Char.AsciiChar = 'o';
//		mainchInfo[temp->y * coord.X + temp->x].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//		temp = temp->back;
//	}
//	mainchInfo[temp->y * coord.X + temp->x].Char.AsciiChar = ' ';
//	mainchInfo[temp->y * coord.X + temp->x].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//	put_screen(&coord, mainchInfo);
//}

struct Point* tailId(struct Point* head) {
	struct Point* temp = head;
	while (temp != NULL) {
		if (temp->back == NULL)
			return temp;
		temp = temp->back;
	}
	return temp;
}

struct Point* snakeEating(int x, int y, struct Point* head) {
	//create a link
	struct Point* link = (struct Point*)malloc(sizeof(struct Point));

	link->x = x;
	link->y = y;

	//point it to old first node
	link->back = head;
	link->front = head->front;
	head->front = link;
	//point first to new first node
	head = link;
	return head;
}
struct Point* snakeAwakening(struct Point* head, int startX, int startY) {
	head->x = startX; //22
	head->y = startY; //22
	head->back = NULL;
	head->front = NULL;
	for (int i = 1; i <= 3; i++) {
		head = snakeEating(head->x, head->y - 1, head);
	}
	return head;
}

void xPlusOne(struct Point* tail) {
	struct Point* temp = tail;
	while (temp->front != NULL) {
		temp->x = temp->front->x;
		temp->y = temp->front->y;
		temp = temp->front;
	}
	temp->x += 1;
	temp->y;
}
void yPlusOne(struct Point* tail) {
	struct Point* temp = tail;
	while (temp->front != NULL) {
		temp->x = temp->front->x;
		temp->y = temp->front->y;
		temp = temp->front;
	}
	temp->x;
	temp->y += 1;
}

void xMinusOne(struct Point* tail) {
	struct Point* temp = tail;
	while (temp->front != NULL) {
		temp->x = temp->front->x;
		temp->y = temp->front->y;
		temp = temp->front;
	}
	temp->x -= 1;
	temp->y;
}
void yMinusOne(struct Point* tail) {
	struct Point* temp = tail;
	while (temp->front != NULL) {
		temp->x = temp->front->x;
		temp->y = temp->front->y;
		temp = temp->front;
	}
	temp->x;
	temp->y -= 1;
}

int snakeBites(struct Point* head) {
	int headX = head->x;
	int headY = head->y;
	struct Point* temp = head;
	temp = temp->back;
	while (temp != NULL) {
		if (headX == temp->x && headY == temp->y)
			return 1;
		temp = temp->back;
	}
	return 0;
}

struct Point* snakeGrow(struct Point* tail) {
	struct Point* link = (struct Point*)malloc(sizeof(struct Point));
	tail->back = link;
	link->x = tail->x+1;
	link->y = tail->y+1;
	link->front = tail;
	link->back = NULL;
	return tail;
}