#define UNICODE

#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>

int startwindow(void);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int file_processing(const wchar_t *buffer);