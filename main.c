#include "framework.h"
#include "functions.h"

// Глобальне переменные:
int BlockSize;
struct Position Start, StartPos, LastPos;

WNDPROC CALLBACK WndProc
(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (message) {
		// Отрисовка окна
	case WM_MOUSEMOVE:
	{
		
	}
	case WM_LBUTTONDOWN:
	{

	}
	case WM_PAINT:
	{
		// Получение координат клиентской части окна
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rcClient;

		GetClientRect(hWnd, &rcClient);

		struct RenderParam CellSizeNow = CellSize(hdc, rcClient);

		CreateChessBoard(hdc, CellSizeNow.x, CellSizeNow.y, CellSizeNow.sx, CellSizeNow.sy);

		Start.x = CellSizeNow.sx;
		Start.y = CellSizeNow.sy;
		BlockSize = CellSizeNow.x;

		// Конец отрисовки, особождение контекста
		EndPaint(hWnd, &ps);
	}
	break;

	// Выход из приложения
	case WM_DESTROY:
		PostQuitMessage(0);

		// Остальные сообщения окна обрабатываются стандартным образом
	default:
		return DefWindowProcA(hWnd, message, wParam, lParam);
	}
	return 0;
}

int main() 
{

	int iCount = 0;

	WNDCLASSA wndclass;

	memset(&wndclass, 0, sizeof(WNDCLASSA));
	wndclass.lpszClassName = "Chess";
	wndclass.lpfnWndProc = WndProc;

	RegisterClassA(&wndclass);

	HWND hwnd;

	hwnd = CreateWindowA
	(
		"Chess",
		"Chess",
		WS_OVERLAPPEDWINDOW,
		10,
		10,
		640,
		480,
		NULL,
		NULL,
		NULL,
		NULL
	);

	ShowWindow(hwnd, SW_SHOWNORMAL);

	MSG msg;

	HDC hdc = GetDC(hwnd);

	struct Position PosNow, CellNow;

	while (GetMessageA(&msg,NULL, 0, 0))
	{
		if (GetKeyState(VK_LBUTTON) < 0 && iCount < 2) {

			PosNow = MouseClickPos(hwnd);

			CellNow = SelectCell(PosNow.x, PosNow.y, Start.x, Start.y, BlockSize);

			if (iCount == 0)
			{
				StartPos = CellNow;
			}
			else
			{
				LastPos = CellNow;
			}

			CreateElp(hwnd, hdc, (Start.x + (CellNow.x) * BlockSize + BlockSize * 0.1), 
				(Start.y + (9-CellNow.y) * BlockSize + BlockSize * 0.1), BlockSize);

			iCount++;
		}
		else if (iCount == 2)
		{

			if (StartPos.x == LastPos.x || StartPos.y == LastPos.y)
			{
				CreateLine(hwnd, hdc, StartPos.x, StartPos.y, LastPos.x, LastPos.y, BlockSize, Start);
			}
			else
			{
				CreateLine(hwnd, hdc, StartPos.x, StartPos.y, LastPos.x, StartPos.y, BlockSize, Start);
				CreateLine(hwnd, hdc, LastPos.x, StartPos.y, LastPos.x, LastPos.y, BlockSize, Start);
			}
		}

		if (msg.message == WM_QUIT) break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		Sleep(10);

	}

}
