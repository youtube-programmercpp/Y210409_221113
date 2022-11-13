// C++サンプルプログラム（ファイル分割例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#include "Tokenizer.h"
#include "InfixReader.h"
#include "Token.h"
#include "TokenCategory.h"

// scan next token
Token 次の字句を得る(InfixReader& input)
{
	switch (input.今見ている文字を読む()) {
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		for (int value = input.今見ている文字を読む() - '0';;) {
			switch (input.次の文字を読む()) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				value *= 10;
				value += input.今見ている文字を読む() - '0';
				continue;
			default:
				return { TokenCategory::正の整数定数, value };
			}
		}
	case '+' : input.次の文字を読む(); return { TokenCategory::プラス       };
	case '-' : input.次の文字を読む(); return { TokenCategory::マイナス     };
	case '*' : input.次の文字を読む(); return { TokenCategory::アスタリスク };
	case '/' : input.次の文字を読む(); return { TokenCategory::スラッシュ   };
	case '(' : input.次の文字を読む(); return { TokenCategory::左括弧       };
	case ')' : input.次の文字を読む(); return { TokenCategory::右括弧       };
	default:
		return  { TokenCategory::不明な文字 };
	}
}
