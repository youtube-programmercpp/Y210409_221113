// C++サンプルプログラム（ファイル分割例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#include "PostfixWriter_cout.h"
#include <iostream>

void PostfixWriter_cout::定数を書く(int value)
{
	std::cout << "定数：" << value << '\n';
}
void PostfixWriter_cout::単項マイナスを書く()
{
	std::cout << "単項演算子：-\n";
}
void PostfixWriter_cout::乗算演算子を書く()
{
	std::cout << "二項演算子：*\n";
}
void PostfixWriter_cout::除算演算子を書く()
{
	std::cout << "二項演算子：/\n";
}
void PostfixWriter_cout::加算演算子を書く()
{
	std::cout << "二項演算子：+\n";
}
void PostfixWriter_cout::減算演算子を書く()
{
	std::cout << "二項演算子：-\n";
}
