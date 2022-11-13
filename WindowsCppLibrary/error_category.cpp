// Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#include "pch.h"
#include "error_category.h"
#include <Windows.h>

const char* WindowsCppLibrary::error_category::LSTATUS::name() const noexcept
{
	return "Windows API";
}
std::string WindowsCppLibrary::error_category::LSTATUS::message(int _Errval) const
{
	std::string buffer;
	constexpr DWORD nSize = 1024;
	buffer.resize(nSize - 1);
	buffer.resize(/*WINBASEAPI _Success_(return != 0) DWORD WINAPI*/FormatMessageA
	( /*_In_     DWORD     dwFlags      */FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK
	, /*_In_opt_ LPCVOID   lpSource     */nullptr
	, /*_In_     DWORD     dwMessageId  */_Errval
	, /*_In_     DWORD     dwLanguageId */0
	, //_When_((dwFlags & FORMAT_MESSAGE_ALLOCATE_BUFFER) != 0, _At_((LPSTR*)lpBuffer, _Outptr_result_z_))
	  //_When_((dwFlags & FORMAT_MESSAGE_ALLOCATE_BUFFER) == 0, _Out_writes_z_(nSize))
	  /*         LPSTR     lpBuffer     */&buffer.front()
	, /*_In_     DWORD     nSize        */nSize
	, /*_In_opt_ va_list * Arguments    */nullptr
	));
	return buffer;
}
