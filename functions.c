#pragma once

#include "framework.h"
#include "functions.h"

struct RenderParam CellSize(HDC hdc, const RECT rc) {

	int width = rc.right - rc.left + 1;		// координатны правого нижнего
	int height = rc.bottom - rc.top + 1;	// угла доски

	int sx = 0;								// кооринаты левого верхнего
	int sy = 0;								// угла доски

	if (width > height) {
		sx = (width - height) / 2;
		width = height;
	}
	else {
		sy = (height - width) / 2;
		height = width;
	}

	struct RenderParam Size = { width / 10, height / 10 , sx ,sy };

	return Size;

}

struct Position MouseClickPos(HWND hwnd) {

	LPPOINT pPnt;
	pPnt = malloc(sizeof(*pPnt));


	if (pPnt)GetCursorPos(pPnt);
	if (pPnt)ScreenToClient(hwnd, pPnt);

	struct Position PosNow = { pPnt[0].x, pPnt[0].y };

	return PosNow;



}

struct Position SelectCell(int xPos, int yPos, int StartX, int StartY, int BlockSize) {

	if (xPos > StartX && yPos > StartY && xPos < (StartX + BlockSize * 9) && yPos < (StartY + BlockSize * 9)) {

		int i = 1;
		int j = 1;

		while ((i + 1) * BlockSize < xPos) {
			i++;
		}

		while ((j + 1) * BlockSize < yPos) {
			j++;
		}

		printf("x: %d	y: %d\n", i - 2, abs(8 - j) + 1);

		struct Position Cell = { i - 2, abs(8 - j) + 1 };

		return Cell;
	}

	struct Position Cell = { -1, -1 };

	return Cell;
}

void CreateChessBoard(HDC hdc, int cell_width, int cell_height, int sx, int sy) {

	HBRUSH white = CreateSolidBrush(RGB(255, 255, 192));	// для белой клеточки
	HBRUSH black = CreateSolidBrush(RGB(0, 0, 80));			// для чёрной клеточки

	// Отрисовка всех клеток доски
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {

			// Выбор цвета клеточки
			SelectObject(hdc, ((i ^ j) & 1) ? black : white);

			// Отрисовка одной клеточки
			int x = sx + (i + 1) * cell_width;
			int y = sy + (j + 1) * cell_height;
			Rectangle(hdc, x, y, x + cell_width, y + cell_height);
		}
	}

	// Удаление кистей
	DeleteObject(white);
	DeleteObject(black);

}

void CreateElp(HWND hwnd, HDC hdc, int xPos1, int yPos1, int BlockSize) {

	HPEN hOldPen;
	HBRUSH hOldBrush;

	HPEN hGreenPen = CreatePen(PS_SOLID, 5, RGB(235, 195, 15));

	HBRUSH hGreenBrush = CreateSolidBrush(RGB(235, 195, 15));

	// нарисовать ладью
	SelectObject(hdc, hGreenPen);
	hOldBrush = SelectObject(hdc, hGreenBrush);
	Ellipse
	(
		hdc,
		xPos1,
		yPos1,
		xPos1 + BlockSize * 0.8,
		yPos1 + BlockSize * 0.8);

	// Удаление кистей
	DeleteObject(hGreenPen);



}

void CreateLine
(
	HWND hwnd, HDC hdc, 
	int xPos1, int yPos1, 
	int xPos2, int yPos2,
	int BlockSize,
	struct Position Start
) {

	HPEN hOldPen;
	HPEN hGreenPen = CreatePen(PS_SOLID, 5, RGB(235, 195, 15));

	// нарисовать линию
	SelectObject(hdc, hGreenPen);

	MoveToEx
	(
		hdc,
		Start.x + xPos1 * BlockSize + BlockSize * 0.5,
		Start.y + (9 - yPos1) * BlockSize + BlockSize * 0.5,
		NULL
	);

	LineTo
	(
		hdc,
		Start.x + xPos2 * BlockSize + BlockSize * 0.5,
		Start.y + (9 - yPos2) * BlockSize + BlockSize * 0.5
	);

	// Удаление кистей
	DeleteObject(hGreenPen);

}