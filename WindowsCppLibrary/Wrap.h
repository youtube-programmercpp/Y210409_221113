// Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#pragma once
#include <Windows.h>
#include <string>
namespace WindowsCppLibrary {
	namespace Wrap {
		inline std::wstring GetWindowTextW(HWND hWnd)
		{
			if (const auto cchTextW = /*WINUSERAPI int WINAPI*/GetWindowTextLengthW(/*_In_ HWND hWnd*/hWnd)) {
				std::wstring sTextW;
				sTextW.resize(cchTextW);
				sTextW.resize(/*_Ret_range_(0, nMaxCount) WINUSERAPI int WINAPI*/GetWindowTextW
					( /*_In_                    HWND   hWnd     */hWnd     
					, /*_Out_writes_(nMaxCount) LPWSTR lpString */&sTextW.front()
					, /*_In_                    int    nMaxCount*/static_cast<int>(1 + sTextW.size())
					)
				);
				return sTextW;
			}
			else
				return {};
		}
		inline std::wstring GetDlgItemTextW
		( _In_opt_ HWND hDlg      
		, _In_     int  nIDDlgItem
		)
		{
			if (const auto hEdit = ::GetDlgItem
			( /*_In_opt_ HWND hDlg      */hDlg      
			, /*_In_     int  nIDDlgItem*/nIDDlgItem
			))
				return GetWindowTextW(hEdit);
			else
				return {};
		}
	}
}
