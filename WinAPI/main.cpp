#include<Windows.h>

INT WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInst, LPSTR ipCmdLine, INT nCmdShow)
{
	MessageBox(
		NULL,
		"Hello Windows!\n Привет...", "Header (Caption)",
		MB_YESNOCANCEL | MB_ICONASTERISK | MB_HELP|
		MB_DEFBUTTON3
	
	);
	return 0;

}