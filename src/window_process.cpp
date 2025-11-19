#include "includes.hpp"

static HWND g_hEdit = nullptr;
static WNDPROC g_EditOldProc = nullptr;

LRESULT CALLBACK EditProc(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CHAR:
		if (wParam == L'\r')
		{
			// read text
			HWND hParentTemp = GetParent(hWindow);
			wchar_t buffer[256] = {};
			GetWindowTextW(hWindow, buffer, 256);
			
			// conversion & processing
			if(!file_processing(buffer))
				MessageBoxW(hWindow, L"File not found bro", NULL, MB_OK);

			// destroy & remove text field
			DestroyWindow(hWindow);
			g_hEdit = nullptr;
			InvalidateRect(hParentTemp, nullptr, TRUE);
    		UpdateWindow(hParentTemp);
			return 0;
		}
		break;
	}
	return CallWindowProcW(g_EditOldProc, hWindow, uMsg, wParam, lParam);
}

void click_button(HWND hWindow, WPARAM wParam)
{
	int id = LOWORD(wParam);
	int code = HIWORD(wParam); // notification code

	if (id == 1 && code == BN_CLICKED)
	{
		if (g_hEdit == 0)
		{
			g_hEdit = CreateWindowExW(
				0,
				L"EDIT", // edit control
				L"",	 // initial text
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
				20, 80,	  // x, y inside main window
				200, 24,  // width, height
				hWindow,	  // parent = main window
				(HMENU)2, // control ID
				GetModuleHandleW(nullptr),
				nullptr);

			g_EditOldProc = (WNDPROC)SetWindowLongPtrW(
				g_hEdit,
				GWLP_WNDPROC,
				(LONG_PTR)EditProc);
		}
		SetFocus(g_hEdit);
	}
}

LRESULT CALLBACK WindowProc(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_COMMAND:
	{
		click_button(hWindow, wParam);
		return 0;
	}
	}
	return DefWindowProc(hWindow, uMsg, wParam, lParam);
}