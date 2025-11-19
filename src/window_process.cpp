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
			std::string filename = file_processing(buffer);
			if (filename.empty())
				MessageBoxW(hWindow, L"File not found bro", NULL, MB_OK);
			else
			{
				filename += ".replace";
				std::wstring message = L"You can find your result here:\n";
				message += std::wstring(filename.begin(), filename.end());
				MessageBoxW(hWindow, message.c_str(), L"Success!", MB_OK);
			}

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
				L"EDIT", L"",
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
				200, 100,
				200, 24,
				hWindow,
				(HMENU)2,
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
