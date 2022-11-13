// C++サンプルプログラム（DLL化実装例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#pragma once
struct InfixReader;
struct PostfixWriter;

#ifdef DLL1_EXPORTS
#	define	DLL1_API __declspec(dllexport)
#else
#	define	DLL1_API __declspec(dllimport)
#endif
DLL1_API void 中置記法から後置記法に変換する(InfixReader& input, PostfixWriter& output);
