// Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#pragma once
#include "errc.h"
#include "SourceLocation.h"
#include <Windows.h>
namespace WindowsCppLibrary {
	namespace RAII {
		class UnregisterClassW
		{
			HINSTANCE hInstance        ;
			ATOM      window_class_atom;
		public:
			UnregisterClassW(HINSTANCE hInstance, ATOM window_class_atom) noexcept;
			UnregisterClassW() noexcept;
			~UnregisterClassW();
			UnregisterClassW(UnregisterClassW&& r) noexcept;
			UnregisterClassW& operator=(UnregisterClassW&& r) noexcept;
			LPCWSTR MakeIntAtom() const noexcept;
		};
	}
}
inline WindowsCppLibrary::RAII::UnregisterClassW::UnregisterClassW(HINSTANCE hInstance, ATOM window_class_atom) noexcept
	: hInstance        { hInstance         }
	, window_class_atom{ window_class_atom }
{
}
inline WindowsCppLibrary::RAII::UnregisterClassW::UnregisterClassW() noexcept
	: UnregisterClassW{ nullptr, 0 }
{
}
inline WindowsCppLibrary::RAII::UnregisterClassW::~UnregisterClassW()
{
	if (window_class_atom) {
		if (!/*WINUSERAPI BOOL WINAPI*/::UnregisterClassW
		( /*_In_     LPCWSTR   lpClassName*/LPCWSTR(window_class_atom)
		, /*_In_opt_ HINSTANCE hInstance  */hInstance
		)) {
#ifdef _DEBUG
			OutputDebugStringA(std::system_error(static_cast<WindowsCppLibrary::errc::LSTATUS>(GetLastError()), SourceLocation "UnregisterClassW failed").what());
			OutputDebugStringA("\n");
#endif
		}
	}
}
inline WindowsCppLibrary::RAII::UnregisterClassW::UnregisterClassW(UnregisterClassW&& r) noexcept
	: UnregisterClassW{ r.hInstance, r.window_class_atom }
{
	r.hInstance         = nullptr;
	r.window_class_atom = 0      ;
}
inline auto WindowsCppLibrary::RAII::UnregisterClassW::operator=(UnregisterClassW&& r) noexcept->UnregisterClassW&
{
	std::swap(hInstance        , r.hInstance        );
	std::swap(window_class_atom, r.window_class_atom);
	return *this;
}
inline LPCWSTR WindowsCppLibrary::RAII::UnregisterClassW::MakeIntAtom() const noexcept
{
	return LPCWSTR(window_class_atom);
}
