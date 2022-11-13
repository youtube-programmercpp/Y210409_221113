// C++サンプルプログラム（DLL化実装例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#pragma once
enum class TokenCategory;
struct Token {
	TokenCategory       字句の種類; //category
	int                 定数値    ; //value   
};
