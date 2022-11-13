// Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#include "MainWindow.h"
#include "resource.h"
#include "DialogDisplayString.h"
#include <Trial_A/MakeSampleString.h>
#include <Trial_A/ParseStr.h>
#include <Trial_B/ParseStr.h>
#include <array>

MainWindow::MainWindow()
	: display_string{Trial_A::MakeSampleString()}
{
}
WindowsCppLibrary::RAII::UnregisterClassW MainWindow::RegisterClassExW(HINSTANCE hInstance)
{
	if (const auto window_class_atom = ::RegisterClassExW(std::array<WNDCLASSEXW, 1>
	{ /*UINT        cbSize       */sizeof (WNDCLASSEXW)
	, /*UINT        style        */CS_HREDRAW | CS_VREDRAW
	, /*WNDPROC     lpfnWndProc  */MainWindow::WindowProc
	, /*int         cbClsExtra   */0
	, /*int         cbWndExtra   */0
	, /*HINSTANCE   hInstance    */hInstance
	, /*HICON       hIcon        */LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_WINDOWSPROJECT1))
	, /*HCURSOR     hCursor      */LoadCursorW(nullptr, IDC_ARROW)
	, /*HBRUSH      hbrBackground*/HBRUSH(COLOR_WINDOW + 1)
	, /*LPCWSTR     lpszMenuName */MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1)
	, /*LPCWSTR     lpszClassName*/L"WINDOWSPROJECT1"
	, /*HICON       hIconSm      */LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_SMALL))
	}.data()))
		return { hInstance, window_class_atom };
	else
		throw std::system_error(static_cast<WindowsCppLibrary::errc::LSTATUS>(GetLastError()), SourceLocation __FUNCTION__ " failed");
}
HWND MainWindow::CreateWindowExW
( _In_opt_   LPCWSTR   lpClassName 
, _In_opt_   HINSTANCE hInstance   
)
{
	if (const auto hWnd = /*WINUSERAPI HWND WINAPI*/::CreateWindowExW
		( /*_In_       DWORD     dwExStyle   */0
		, /*_In_opt_   LPCWSTR   lpClassName */lpClassName
		, /*_In_opt_   LPCWSTR   lpWindowName*/L"WindowsProject1"
		, /*_In_       DWORD     dwStyle     */WS_OVERLAPPEDWINDOW
		, /*_In_       int       X           */CW_USEDEFAULT
		, /*_In_       int       Y           */0
		, /*_In_       int       nWidth      */CW_USEDEFAULT
		, /*_In_       int       nHeight     */0
		, /*_In_opt_   HWND      hWndParent  */nullptr
		, /*_In_opt_   HMENU     hMenu       */nullptr
		, /*_In_opt_   HINSTANCE hInstance   */hInstance
		, /*_In_opt_   LPVOID    lpParam     */this
		))
		return hWnd;
	else
		throw std::system_error(static_cast<WindowsCppLibrary::errc::LSTATUS>(GetLastError()), SourceLocation __FUNCTION__ " failed");
}
//バージョン情報ダイアログボックス
static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, IDOK);
			return true;
		default:
			return false;
		}
	default:
		return false;
	}
}
void MainWindow::Handle_WM_PAINT(HWND hWnd)
{
// 受領日：2022/11/13(日)
// 原作者：GoldSmith さん
// 備考：Trial_A と Trial_B で比較できるよう当方にて一部変更しました。
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	//対象の文字列
	//basic_string<TCHAR> tstr(_T("\x1b[2JHellow\r\n"));
	//テキストアラインモード設定
	UINT DefTA = GetTextAlign(hdc);
	MoveToEx(hdc, 100, 100, NULL);
	SetTextAlign(hdc, DefTA & ~TA_NOUPDATECP | TA_UPDATECP);

	//
	//	Trial_A 版を試す
	//
	Trial_A::ParseStr(display_string, 0, ps);
	//
	//	Trial_B 版を試す
	//
	MoveToEx(hdc, 100, 200, NULL);
	Trial_B::ParseStr(display_string, 0, ps);


	SetTextAlign(hdc, DefTA);
	EndPaint(hWnd, &ps);
}
LRESULT MainWindow::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (message) {
	case WM_COMMAND:
		//メニュー操作が行われた際の対処
		switch (LOWORD(wParam)) {
		case ID_SETTINGS_DisplayString:
			try {
				//ダイアログボックスを用いて表示文字列の設定を変更する
				DialogDisplayString dialog;
				dialog.value = display_string;
				if (dialog.DialogBoxParamW(hWnd) == IDOK) {
					//OKがクリックされたので表示文字列を更新する
					display_string = dialog.value;
					//表示を更新する（無効化して更新）
					InvalidateRect(hWnd, nullptr, true);
					UpdateWindow(hWnd);
				}
			}
			catch (const std::exception& e) {
				MessageBoxA(hWnd, e.what(), "Error", MB_ICONSTOP);
			}
			return 0;
		case IDM_ABOUT:
			/*WINUSERAPI INT_PTR WINAPI*/::DialogBoxParamW
			( /*_In_opt_ HINSTANCE hInstance     */HINSTANCE(GetWindowLongPtrW(hWnd, GWLP_HINSTANCE))
			, /*_In_     LPCWSTR   lpTemplateName*/MAKEINTRESOURCEW(IDD_ABOUTBOX)
			, /*_In_opt_ HWND      hWndParent    */hWnd
			, /*_In_opt_ DLGPROC   lpDialogFunc  */About
			, /*_In_     LPARAM    dwInitParam   */0
			);
			return 0;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			return 0;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	case WM_PAINT:
		//クライアント領域の表示
		Handle_WM_PAINT(hWnd);
		return 0;
	case WM_NCDESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

LRESULT CALLBACK MainWindow::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept
{
	if (const auto pThis = reinterpret_cast<MainWindow*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA))) {
		//WM_CREATE到来後のメッセージを処理する
		return pThis->HandleMessage(hWnd, message, wParam, lParam);
	}
	else if (message == WM_CREATE) {
		//this ポインタを設定する
		SetWindowLongPtrW(hWnd, GWLP_USERDATA, LONG_PTR(LPCREATESTRUCT(lParam)->lpCreateParams));
		return 0;
	}
	else {
		//WM_CREATE以前のメッセージを転送
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
