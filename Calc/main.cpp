#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_CLASSNAME[] = "Calc";

CONST INT START_X = 10;
CONST INT START_Y = 10;

CONST INT BUTTON_SIZE = 50;
CONST INT INTERVAL = 10;
CONST INT BUTTON_DOUBLE_SIZE = BUTTON_SIZE * 2 + INTERVAL;

CONST INT SCREEN_WIDTH = (BUTTON_SIZE)*5+INTERVAL*4;
CONST INT SCREEN_HEIGHT = 20;

CONST INT BUTTON_START_X = START_X;
CONST INT BUTTON_START_Y = START_Y + SCREEN_HEIGHT + INTERVAL * 2;

CONST CHAR* OPERATIONS[] = { "/","*","-","+" };

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPrarm);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmsLine, INT nCMDShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;

	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);

	wc.hInstance = hInstance;
	wc.lpszClassName = g_sz_CLASSNAME;
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK);
		return 0;
	}

	HWND hwnd = CreateWindowEx
	(
		NULL, g_sz_CLASSNAME,
		g_sz_CLASSNAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		(BUTTON_SIZE+INTERVAL)*5+BUTTON_START_X*3, SCREEN_HEIGHT+(BUTTON_SIZE+INTERVAL)*5+INTERVAL*2,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK);
		return 0;
	}
	ShowWindow(hwnd, nCMDShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "",
			WS_CHILDWINDOW | WS_VISIBLE |WS_BORDER| ES_RIGHT | ES_READONLY,
			START_X, START_Y,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);
		int digit = 0;
		char sz_digit[2] = "";
		for (int i = 6;i >= 0;i -= 3)
		{
			for (int j = 0;j < 3;j++)
			{
				digit++;
				sz_digit[0] = digit + 48;
				CreateWindowEx
				(
					NULL, "Button", sz_digit,
					WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
					BUTTON_START_X + (BUTTON_SIZE + INTERVAL) * j,
					BUTTON_START_Y + (BUTTON_SIZE + INTERVAL) * i / 3,
					BUTTON_SIZE, BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_0 + digit),
					GetModuleHandle(NULL),
					NULL
				);
			}
		}
		CreateWindowEx(NULL, "Button", "0",
			WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_START_X, BUTTON_START_Y + (BUTTON_SIZE + INTERVAL) * 3,
			BUTTON_DOUBLE_SIZE, BUTTON_SIZE,
			hwnd,
			(HMENU)(IDC_BUTTON_0),
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_START_X + BUTTON_DOUBLE_SIZE + INTERVAL, BUTTON_START_Y + (BUTTON_SIZE + INTERVAL) * 3,
			BUTTON_SIZE, BUTTON_SIZE,
			hwnd,
			(HMENU)(IDC_BUTTON_POINT),
			GetModuleHandle(NULL),
			NULL
		);

		for (int i = 0;i < sizeof(OPERATIONS) / sizeof(OPERATIONS[0]);i++)
		{
		CreateWindowEx
		(
			NULL, "Button", OPERATIONS[i],
			WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_START_X + (BUTTON_SIZE + INTERVAL) * 3,
			BUTTON_START_Y + (BUTTON_SIZE + INTERVAL) * i,
			BUTTON_SIZE, BUTTON_SIZE,
			hwnd,
			(HMENU)(IDC_BUTTON_SLASH-i),
			GetModuleHandle(NULL),
			NULL
		);
		}
		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_START_X + (BUTTON_SIZE + INTERVAL) * 4, BUTTON_START_Y,
			BUTTON_SIZE, BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLEAR,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_START_X + (BUTTON_SIZE + INTERVAL) * 4, BUTTON_START_Y+BUTTON_DOUBLE_SIZE+INTERVAL,
			BUTTON_SIZE, BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);
	
	}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9 || LOWORD(wParam) == IDC_BUTTON_POINT)
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			CHAR sz_buffer[MAX_PATH]{};
			SendMessage(hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)sz_buffer);
			CHAR sz_digit[2]{};
			if (LOWORD(wParam) == IDC_BUTTON_POINT)
			{
				if (strchr(sz_buffer, '.'))break;
				sz_digit[0] = '.';
			}
			else sz_digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + 48;
			strcat(sz_buffer, sz_digit);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
	}
		break;
	case WM_DESTROY: PostQuitMessage(0);break;
	case WM_CLOSE: DestroyWindow(hwnd);break;
	default:	return DefWindowProc(hwnd, uMsg, wParam, lParam);break;
	}
	return NULL;
}