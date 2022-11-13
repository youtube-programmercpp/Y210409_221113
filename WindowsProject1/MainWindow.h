// Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#pragma once
#include <WindowsCppLibrary/RAII.h>
#include <string>
class MainWindow
{
	std::wstring display_string;

	//WM_PAINTメッセージを処理する
	void Handle_WM_PAINT(HWND hWnd);
	//WM_CREATE以降のウィンドウメッセージを処理する
	LRESULT HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;
	//WM_CREATEが到来するまでメッセージを処理する
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;
public:
	MainWindow();
	//ウィンドウクラスを登録する
	static WindowsCppLibrary::RAII::UnregisterClassW RegisterClassExW(HINSTANCE hInstance);
	//ウィンドウを作成する
	HWND CreateWindowExW
	( _In_opt_   LPCWSTR   lpClassName 
	, _In_opt_   HINSTANCE hInstance   
	);
};
