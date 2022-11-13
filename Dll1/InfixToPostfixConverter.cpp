// C++サンプルプログラム（DLL化実装例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#include "pch.h"
#include "InfixToPostfixConverter.h"
#include "Parser.h"
#include "Tokenizer.h"
#include "Token.h"

// convert notation from infix to postfix
DLL1_API void 中置記法から後置記法に変換する(InfixReader& input, PostfixWriter& output)
{
	加減算式を処理する(input, 次の字句を得る(input), output);
}
