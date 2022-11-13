// Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#pragma once
#include <Windows.h>
#include <string>
class DialogDisplayString
{
	std::wstring display_string; //表示文字列

	static INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) noexcept;
	void Handle_WM_INITDIALOG(HWND hDlg);
	INT_PTR HandleMessage(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) noexcept;
public:
	INT_PTR DialogBoxParamW(_In_ HWND hWndParent);

	std::wstring get_value() const;
	void put_value(const std::wstring& display_string);
	__declspec(property(get = get_value, put = put_value)) std::wstring value;
};

