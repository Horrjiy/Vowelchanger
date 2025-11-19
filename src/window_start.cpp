#include "includes.hpp"

int startwindow(void)
{
	HINSTANCE hInstance = GetModuleHandleW(nullptr);
	int nCmdShow = SW_SHOWDEFAULT;

	const wchar_t CLASS_NAME[] = L"SampleWindowClass";
	WNDCLASSW wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hbrBackground = (HBRUSH)(4);

	if (!RegisterClassW(&wc))
		return 0;

	HWND hWindow = CreateWindowExW(
		0,
		CLASS_NAME,
		L"Vowelchanger",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		600, 300,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	if (!hWindow)
		return 0;

	ShowWindow(hWindow, nCmdShow);

	CreateWindowExW(
		0,
		L"BUTTON",
		L"Insert file name!",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		200, 150,
		200, 50,
		hWindow,
		(HMENU)1,
		hInstance,
		nullptr);

	CreateWindowExW(
		0,
		L"STATIC",
		L"Welcome to the Vowelchanger!",
		WS_CHILD | WS_VISIBLE,
		150, 50,
		300, 30,
		hWindow,
		(HMENU)1,
		hInstance,
		nullptr);

	MSG msg = {};
	while (GetMessageW(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}
