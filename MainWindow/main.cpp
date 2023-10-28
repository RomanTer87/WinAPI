#include<Windows.h>
#include"resource.h"

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

	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_CPU));
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_RAM));	//Sm - small
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
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
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:PostQuitMessage(0); break;
	case WM_CLOSE:  DestroyWindow(hwnd);break;
	default:	return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return NULL;
}