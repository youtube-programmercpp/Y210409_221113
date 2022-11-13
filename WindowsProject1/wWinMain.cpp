// WindowsProject1.cpp : Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#include "MainWindow.h"
#include "resource.h"
#pragma comment(lib, "WindowsCppLibrary")
#pragma comment(lib, "Trial_A")
#pragma comment(lib, "Trial_B")

int APIENTRY wWinMain
( _In_     HINSTANCE hInstance    
, _In_opt_ HINSTANCE hPrevInstance
, _In_     LPWSTR    lpCmdLine    
, _In_     int       nCmdShow     
)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	try {
		const auto window_class = MainWindow::RegisterClassExW(hInstance);
		MainWindow mainWindow;
		const auto hWnd = mainWindow.CreateWindowExW(window_class.MakeIntAtom(), hInstance);
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
		for (const auto hAccelTable = LoadAcceleratorsW(hInstance, MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1));;) {
			MSG msg;
			switch (GetMessageW(&msg, nullptr, 0, 0)) {
			case 0:
				return static_cast<int>(msg.wParam);
			case -1:
				return EXIT_FAILURE;
			default:
				if (TranslateAcceleratorW(msg.hwnd, hAccelTable, &msg))
					continue;
				else {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					continue;
				}
			}
		}
	}
	catch (const std::exception& e) {
		OutputDebugStringA(e.what());
		OutputDebugStringA("\n");
		return EXIT_FAILURE;
	}
}
