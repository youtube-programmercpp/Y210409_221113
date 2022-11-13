// Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#include "pch.h"
#include "ParseStr.h"
#include <map>
#include <tchar.h>
namespace Trial_B {
	class MapSpecialCharToKeyword {
		std::map<TCHAR, std::basic_string<TCHAR>> mapCode;
		void Draw
		( _In_              HDC          hdc     
		, _In_opt_          CONST RECT * lprect  
		, _In_reads_opt_(c) LPCTSTR      lpString
		, _In_              UINT         c       
		) const noexcept
		{
			(void)/*WINGDIAPI BOOL WINAPI*/ExtTextOut
			( /*_In_              HDC          hdc     */hdc        
			, /*_In_              int          x       */0          
			, /*_In_              int          y       */0          
			, /*_In_              UINT         options */ETO_CLIPPED
			, /*_In_opt_          CONST RECT * lprect  */lprect     
			, /*_In_reads_opt_(c) LPCTSTR      lpString*/lpString   
			, /*_In_              UINT         c       */c          
			, /*_In_reads_opt_(c) CONST INT  * lpDx    */nullptr    
			);
		}
		void Draw
		( _In_              HDC          hdc     
		, _In_opt_          CONST RECT * lprect  
		, const std::basic_string<TCHAR>& s       
		) const noexcept
		{
			Draw(hdc, lprect, s.c_str(), static_cast<UINT>(s.length()));
		}
		std::pair<const TCHAR*, decltype(mapCode)::const_iterator> 登録された文字を探す
		( _In_ const TCHAR* pchCurrent
		, _In_ const TCHAR* pchEnd    
		) const noexcept
		{
			for (;;) {
				if (pchCurrent < pchEnd) {
					const auto it = mapCode.find(*pchCurrent);
					if (it == mapCode.end()) {
						++pchCurrent;
						continue;
					}
					else
						return { pchCurrent, it };
				}
				else
					return { pchCurrent, mapCode.end()};
			}
		}
		void 登録された文字とそれ以降を表示
		( _In_              HDC             hdc                 
		, _In_opt_          CONST RECT *    lprect              
		, _In_              const TCHAR*    pchRegistered       
		, _In_              const TCHAR*    pchEnd              
		, decltype(mapCode)::const_iterator itRegisteredMapEntry
		) const noexcept
		{
			const COLORREF previous_color = SetTextColor(hdc, RGB(0, 127, 127));
			for (;;) {
				Draw(hdc, lprect, itRegisteredMapEntry->second);
				const auto pchNext = pchRegistered + 1;
				if (pchNext == pchEnd) {
					(void)SetTextColor(hdc, previous_color);
					break;
				}
				else if ((itRegisteredMapEntry = mapCode.find(*pchNext)) == mapCode.end()) {
					(void)SetTextColor(hdc, previous_color);
					登録されていない文字とそれ以降を表示(hdc, lprect, pchNext, pchEnd);
					break;
				}
				else
					pchRegistered = pchNext;
			}
		}
		void 登録されていない文字とそれ以降を表示
		( _In_              HDC          hdc            
		, _In_opt_          CONST RECT * lprect         
		, _In_              const TCHAR* pchUnregistered
		, _In_              const TCHAR* pchEnd         
		) const noexcept
		{
			const auto next_char = 登録された文字を探す(pchUnregistered + 1, pchEnd);
			Draw(hdc, lprect, &*pchUnregistered, static_cast<UINT>(next_char.first - pchUnregistered));
			if (next_char.first == pchEnd)
				return;
			else
				登録された文字とそれ以降を表示(hdc, lprect, next_char.first, pchEnd, next_char.second);
		}
	public:
		MapSpecialCharToKeyword()
			: mapCode
				{ {_T('\x1b'), _T("ESC")}
				, {_T('\r'  ), _T("\\r")}
				, {_T('\n'  ), _T("\\n")}
				}
		{
		}
		void ConvAndDraw
		( _In_              HDC           hdc     
		, _In_opt_          CONST RECT  * lprect  
		, _In_              const TCHAR* pchFirst 
		, _In_              const TCHAR* pchEnd   
		) const noexcept
		{
			if (pchFirst < pchEnd) {
				auto it = mapCode.find(*pchFirst);
				if (it == mapCode.end())
					登録されていない文字とそれ以降を表示(hdc, lprect, pchFirst, pchEnd);
				else
					登録された文字とそれ以降を表示(hdc, lprect, pchFirst, pchEnd, it);
			}
		}
	};
	void ParseStr(const std::basic_string<TCHAR> & str, size_t pos, const PAINTSTRUCT& ps);
}
void Trial_B::ParseStr(const std::basic_string<TCHAR> & str, size_t pos, const PAINTSTRUCT& ps)
{
	if (pos < str.length()) {
		MapSpecialCharToKeyword{}.ConvAndDraw(ps.hdc, &ps.rcPaint, &str[pos], &str.back() + 1);
	}
}
