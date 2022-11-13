// Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#include "DialogDisplayString.h"
#include "EscapeSequence.h"
#include <WindowsCppLibrary/Wrap.h>
#include "resource.h"

INT_PTR CALLBACK DialogDisplayString::DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) noexcept
{
	if (const auto pThis = reinterpret_cast<DialogDisplayString*>(GetWindowLongPtrW(hDlg, DWLP_USER))) {
		//WM_INITDIALOG以降のメッセージを処理する
		return pThis->HandleMessage(hDlg, message, wParam, lParam);
	}
	else if (message == WM_INITDIALOG) {
		SetWindowLongPtrW(hDlg, DWLP_USER, lParam);
		reinterpret_cast<DialogDisplayString*>(lParam)->Handle_WM_INITDIALOG(hDlg);
		return true;
	}
	else
		return false;//WM_INITDIALOG以前のメッセージだったので処理しない
}
void DialogDisplayString::Handle_WM_INITDIALOG(HWND hDlg)
{
	//表示文字列（制御文字はエスケープシーケンスで表現）を画面に設定する
	SetDlgItemTextW(hDlg, IDC_EDIT_DisplayText, EscapeSequence::Encode<std::wstring>(display_string, EscapeSequence::Hex{}).c_str());
}
INT_PTR DialogDisplayString::HandleMessage(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (message) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			//表示文字列（エスケープシーケンスは制御文字に変換）を画面から読み取る
			try {
				display_string = EscapeSequence::Decode(WindowsCppLibrary::Wrap::GetDlgItemTextW(hDlg, IDC_EDIT_DisplayText));
				EndDialog(hDlg, IDOK);
				return true;
			}
			catch (const std::exception& e) {
				MessageBoxA(hDlg, e.what(), "Error", MB_ICONSTOP);
				return false;
			}
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return true;
		default:
			return false;
		}
	default:
		return false;
	}
}
INT_PTR DialogDisplayString::DialogBoxParamW(_In_ HWND hWndParent)
{
	return /*WINUSERAPI INT_PTR WINAPI*/::DialogBoxParamW
	( /*_In_opt_ HINSTANCE hInstance     */HINSTANCE(GetWindowLongPtrW(hWndParent, GWLP_HINSTANCE))
	, /*_In_     LPCWSTR   lpTemplateName*/MAKEINTRESOURCEW(IDD_DIALOG_DisplayString)
	, /*_In_opt_ HWND      hWndParent    */hWndParent
	, /*_In_opt_ DLGPROC   lpDialogFunc  */DialogProc
	, /*_In_     LPARAM    dwInitParam   */LPARAM(this)
	);
}
std::wstring DialogDisplayString::get_value() const
{
	return display_string;
}
void DialogDisplayString::put_value(const std::wstring& display_string)
{
	this->display_string = display_string;
}
