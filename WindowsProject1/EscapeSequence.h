// Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#pragma once
#include <Windows.h>
#include <string>
#include <stdexcept>
namespace EscapeSequence {
	inline BOOL IsDBCSLeadByte(char TestChar)
	{
		return ::IsDBCSLeadByte(/*_In_ BYTE TestChar*/TestChar);
	}
	inline BOOL IsDBCSLeadByte(wchar_t TestChar)
	{
		return false;
	}
	struct Oct {
		template<class T>void operator()(T& s, unsigned char ch) const
		{
			s.append(1, '\\');
			if (ch == 0)
				s.append(1, '0');
			else {
				for (auto nDigits = 3;;) {
					s.append(1, ((ch >> (3 * --nDigits)) & 7) + '0');
					if (nDigits == 0)
						break;
				}
			}
		}
		template<class T>void operator()(T& s, wchar_t ch) const
		{
			if (ch > UCHAR_MAX)
				throw std::invalid_argument(__FUNCTION__);
			else
				return (*this)(s, static_cast<unsigned char>(ch));
		}
		template<class T, class value_t>static bool Decode(T ch, value_t& rVal)
		{
			if (ch >= '0' && ch <= '7') {
				(rVal <<= 3) += ch - '0';
				return true;
			} else
				return false;
		}
	};
	struct Hex {
		template<class T>void operator()(T& s, typename T::value_type ch) const
		{
			s.append(1, '\\');
			s.append(1, 'x' );
			for (auto nDigits = ch > UCHAR_MAX ? 2 * sizeof ch : 2;;) {
				const unsigned char digit_value = (ch >> (4 * --nDigits)) & 0xf;
				s.append(1, digit_value + (digit_value < 10 ? '0' : ('A' - 10)));
				if (nDigits == 0)
					break;
			}
		}
		template<class T, class value_t>static bool Decode(T ch, value_t& rVal)
		{
			if ('0' <= ch && ch <= '9') {
				(rVal <<= 4) += ch - '0';
				return true;
			} else if ('A' <= ch && ch <= 'F') {
				(rVal <<= 4) += ch - ('A' - 10);
				return true;
			} else if ('a' <= ch && ch <= 'f') {
				(rVal <<= 4) += ch - ('a' - 10);
				return true;
			} else
				return false;
		}
	};
	template<class T, class NumericEncoderType>void         Encode(T& s, typename T::const_pointer first  , typename T::const_pointer last, const NumericEncoderType& numericEncoder)
	{
		while (first < last) {
			switch (*first) {
			case '\n': s.append(1, '\\'); s.append(1, 'n' ); ++first; continue;
			case '\t': s.append(1, '\\'); s.append(1, 't' ); ++first; continue;
			case '\v': s.append(1, '\\'); s.append(1, 'v' ); ++first; continue;
			case '\b': s.append(1, '\\'); s.append(1, 'b' ); ++first; continue;
			case '\r': s.append(1, '\\'); s.append(1, 'r' ); ++first; continue;
			case '\f': s.append(1, '\\'); s.append(1, 'f' ); ++first; continue;
			case '\a': s.append(1, '\\'); s.append(1, 'a' ); ++first; continue;
			case '\\': s.append(1, '\\'); s.append(1, '\\'); ++first; continue;
			case '\0': s.append(1, '\\'); s.append(1, '0' ); ++first; continue;
			case '"' : s.append(1, '\\'); s.append(1, '"' ); ++first; continue;
			case 0x7f: numericEncoder(s, *first++)                  ; continue;
			default:
				if (*first >= 0 && *first < 32) {
					numericEncoder(s, *first++);
					continue;
				}
				else if (IsDBCSLeadByte(*first)) {
					s.append(first, 2);
					first += 2;
					continue;
				}
				else {
					s.append(1, *first++);
					continue;
				}
			}
		}
	}
	template<class T, class NumericEncoderType>T            Encode(      typename T::const_pointer first  , size_t cchText                , const NumericEncoderType& numericEncoder)
	{
		T retval;
		retval.reserve(cchText);
		Encode(retval, first, &first[cchText], numericEncoder);
		return retval;
	}
	template<class T, class NumericEncoderType>T            Encode(const    T& sText, const NumericEncoderType& numericEncoder)
	{
		return Encode<T           >(sText.c_str(), sText.length(), numericEncoder);
	}
	template<         class NumericEncoderType>std:: string Encode(      const  char             * pszText                                , const NumericEncoderType& numericEncoder)
	{
		return Encode<std:: string>(pszText, lstrlenA(pszText), numericEncoder);
	}
	template<         class NumericEncoderType>std::wstring Encode(      const wchar_t           * pszText                                , const NumericEncoderType& numericEncoder)
	{
		return Encode<std::wstring>(pszText, lstrlenW(pszText), numericEncoder);
	}

	template<class T>bool                                   Decode(T& s, typename T::const_pointer first  , typename T::const_pointer last                                           )
	{
		while (first < last) {
			if (*first == '\\') {
				if (++first < last) {
					switch (*first) {
					case 'n' : s.append(1, '\n'); ++first; continue;
					case 't' : s.append(1, '\t'); ++first; continue;
					case 'v' : s.append(1, '\v'); ++first; continue;
					case 'b' : s.append(1, '\b'); ++first; continue;
					case 'r' : s.append(1, '\r'); ++first; continue;
					case 'f' : s.append(1, '\f'); ++first; continue;
					case 'a' : s.append(1, '\a'); ++first; continue;
					case '\\': s.append(1, '\\'); ++first; continue;
					case '"' : s.append(1, '"' ); ++first; continue;
					case 'x':
						if (++first < last) {
							s.append(1, '\0');
							if (Hex::Decode(*first, s.back())) {
								while (++first < last && Hex::Decode(*first, s.back()))
									;
								continue;
							} else
								return false;
						} else
							return false;
					default:
						s.append(1, '\0');
						if (Oct::Decode(*first, s.back())) {
							while (++first < last && Oct::Decode(*first, s.back()))
								;
							continue;
						} else
							return false;
					}
				} else
					return false;
			} else if (IsDBCSLeadByte(*first)) {
				s.append(first, 2);
				first += 2;
				continue;
			}
			else {
				s.append(1, *first++);
				continue;
			}
		}
		return true;
	}
	template<class T>T                                      Decode(      typename T::const_pointer first  , size_t cchText                                                           )
	{
		T s;
		if (Decode(s, first, &first[cchText]))
			return s;
		else
			throw std::invalid_argument(__FUNCTION__);
	}
	inline
	std:: string                                            Decode(      const  char             * pszText                                                                           )
	{
		if (pszText)
			return Decode<std:: string>(pszText, lstrlenA(pszText));
		else
			return {};
	}
	inline
	std::wstring                                            Decode(      const wchar_t           * pszText                                                                           )
	{
		if (pszText)
			return Decode<std::wstring>(pszText, lstrlenW(pszText));
		else
			return {};
	}
	template<class T>T                                      Decode(      const T                 & sText                                                                             )
	{
		if (sText.empty())
			return {};
		else
			return Decode<T>(&sText.front(), sText.length());
	}
}
