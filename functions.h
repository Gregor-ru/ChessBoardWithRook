#pragma once

struct Position
{
	int x, y;
};

struct RenderParam
{
	int x, y;
	int sx, sy;
};

struct RenderParam CellSize(HDC hdc, const RECT rc);
struct Position MouseClickPos(HWND hwnd);
struct Position SelectCell(int xPos, int yPos, int StartX, int StartY, int BlockSize);

void CreateChessBoard(HDC hdc, int cell_width, int cell_height, int sx, int sy);
void CreateElp(HWND hwnd, HDC hdc, int xPos1, int yPos1, int BlockSize);
void CreateLine
(
	HWND hwnd, HDC hdc,
	int xPos1, int yPos1,
	int xPos2, int yPos2,
	int BlockSize,
	struct Position Start
);