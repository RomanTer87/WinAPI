#include<Windows.h>
#include"resource.h"

#define IDC_COMBO	1001
#define IDC_BUTTON_APPLY	1002
CONST CHAR* g_CURSOR[] = { "Busy.ani", "Normal Select.ani","Working In Background.ani" };

CONST CHAR g_sz_WINDOW_CLASS[] = "My Window Class"; // ��� ������ ����

LRESULT CALLBACK WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) ����������� ������ ����:
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);
	// �cb - Count Bytes (���������� ����)
	wc.cbWndExtra = 0; // �������������� ����� ����
	wc.cbClsExtra = 0; // �������������� ����� ������ ����
	wc.style = 0;	// ����� ����

	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_CPU));
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_RAM));	//Sm - small
	wc.hIcon = (HICON)LoadImage(hInstance, "Gift.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "Reward.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hCursor = (HCURSOR)LoadImage(hInstance, "star.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hbrBackground = HBRUSH(COLOR_WINDOW + 1);

	wc.hInstance = hInstance; // hInstance - ��� ��������� ������������ ����� ��������� � ������;
	// ������� WinMain() ��������� hInstance ��� ��������, � ������� � ���� ���� ������ ������,
	// � ����� ������ ������� 'hInstance' ������ ����� �������� ��� ������ ������� GetModuleHandle (NULL)
	wc.lpfnWndProc = WndProc; // ��������� �� ��������� ����
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_WINDOW_CLASS;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class Registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	//2) �������� ����:
	HWND hwnd = CreateWindowEx
	(
		NULL,	// ExStyle
		g_sz_WINDOW_CLASS,	// Class name
		g_sz_WINDOW_CLASS,	// Window name
		WS_OVERLAPPEDWINDOW, // � �������� ���� ������ ����� ����� �����
		CW_USEDEFAULT, CW_USEDEFAULT, // Position - ��������� ���� �� ������
		CW_USEDEFAULT, CW_USEDEFAULT, // Size - ������ ����
		NULL,	//Parent window
		NULL,	//hMenu - ��� �������� ���� ���� �������� �������� ID_������� ����
		// ��� ��������� ����, ������� �������� ��������� ������� ����, � hMenu ���������� ID_������� ����� ��������
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//3) ������ ����� ���������:
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hCombo = CreateWindowEx
		(
			NULL,
			"ComboBox",
			"",
			WS_CHILD | WS_VISIBLE | CBN_DROPDOWN,
			10, 10,
			200, 200,
			hwnd,
			(HMENU)IDC_COMBO,
			GetModuleHandle(NULL),
			NULL
		);
		for (int i = 0;i < sizeof(g_CURSOR) / sizeof(g_CURSOR[0]);i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_CURSOR[i]);
		}

		HWND hButton = CreateWindowEx
		(
			NULL,
			"Button",
			"Apply",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			220, 10,
			100, 28,
			hwnd,
			(HMENU)IDC_BUTTON_APPLY,
			GetModuleHandle(NULL),
			NULL
		);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_APPLY:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
			int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			CHAR sz_filename[_MAX_FNAME]{};
		}
		break;
		}
	}
		break;
	case WM_DESTROY:PostQuitMessage(0); break;
	case WM_CLOSE:  DestroyWindow(hwnd);break;
	default:	return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return NULL;
}