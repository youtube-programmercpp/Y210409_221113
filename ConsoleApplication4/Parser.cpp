// C++サンプルプログラム（ファイル分割例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#include "Parser.h"
#include "Token.h"
#include "TokenCategory.h"
#include "InfixReader.h"
#include "PostfixWriter.h"
#include "Tokenizer.h"

//parse primary expression
Token 一次式を処理する(InfixReader& input, Token 解析対象字句, PostfixWriter& output)
{
	switch (解析対象字句.字句の種類) {
	case TokenCategory::左括弧:
		解析対象字句 = 加減算式を処理する(input, 次の字句を得る(input), output);
		if (解析対象字句.字句の種類 == TokenCategory::右括弧)
			return 次の字句を得る(input);
		else
			return { TokenCategory::不明な文字 };
	case TokenCategory::正の整数定数:
		output.定数を書く(解析対象字句.定数値);
		return 次の字句を得る(input);
	default:
		return { TokenCategory::不明な文字 };
	}
}
//parse unary expression
Token 単項式を処理する(InfixReader& input, Token 解析対象字句, PostfixWriter& output)
{
	switch (解析対象字句.字句の種類) {
	case TokenCategory::プラス  : 解析対象字句 = 単項式を処理する(input, 次の字句を得る(input), output);                              return 解析対象字句;
	case TokenCategory::マイナス: 解析対象字句 = 単項式を処理する(input, 次の字句を得る(input), output); output.単項マイナスを書く(); return 解析対象字句;
	default:
		return 一次式を処理する(input, 解析対象字句, output);
	}
}
//parse multiplicative expression
Token 乗除算式を処理する(InfixReader& input, Token 解析対象字句, PostfixWriter& output)
{
	解析対象字句 = 単項式を処理する(input, 解析対象字句, output);
	for (;;) {
		switch (解析対象字句.字句の種類) {
		case TokenCategory::アスタリスク: 解析対象字句 = 単項式を処理する(input, 次の字句を得る(input), output); output.乗算演算子を書く(); continue;
		case TokenCategory::スラッシュ  : 解析対象字句 = 単項式を処理する(input, 次の字句を得る(input), output); output.除算演算子を書く(); continue;
		default:
			return 解析対象字句;
		}
	}
}
//parse additive expression
Token 加減算式を処理する(InfixReader& input, Token 解析対象字句, PostfixWriter& output)
{
	for (解析対象字句 = 乗除算式を処理する(input, 解析対象字句, output);;) {
		switch (解析対象字句.字句の種類) {
		case TokenCategory::プラス  : 解析対象字句 = 乗除算式を処理する(input, 次の字句を得る(input), output); output.加算演算子を書く(); continue;
		case TokenCategory::マイナス: 解析対象字句 = 乗除算式を処理する(input, 次の字句を得る(input), output); output.減算演算子を書く(); continue;
		default:
			return 解析対象字句;
		}
	}
}
