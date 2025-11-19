// 1
// ~-~-~-~-~-~-~ Definitions ~-~-~-~-~-~-~ //

#ifndef INCLUDES_HPP
#define INCLUDES_HPP
#define UNICODE

// 2
// ~-~-~-~-~-~-~ Includes ~-~-~-~-~-~-~ //

#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>

// 3
// ~-~-~-~-~-~-~ Functions ~-~-~-~-~-~-~ //

int startwindow(void);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
std::string file_processing(const wchar_t *buffer);

#endif /* INCLUDES_HPP */
