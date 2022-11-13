// C++サンプルプログラム：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
enum class TokenCategory
{ 不明な文字   // unknown character
, 正の整数定数 // positive integer constant
, プラス       // '+' plus
, マイナス     // '-' minus
, アスタリスク // '*' asterisk
, スラッシュ   // '/' slash
, 左括弧       // '(' left parenthesis
, 右括弧       // ')' right parenthesis
};
struct Token {
	TokenCategory       字句の種類; //category
	int                 定数値    ; //value   
};

struct InfixReader {
	// read current character
	virtual int 今見ている文字を読む   () = 0;
	// read next character
	virtual int 次の文字を読む         () = 0;
};
struct PostfixWriter {
	// write constant
	virtual void 定数を書く        (int value) = 0;
	// write unary minus operator
	virtual void 単項マイナスを書く() = 0;
	// write multiplication operator
	virtual void 乗算演算子を書く  () = 0;
	// write division operator
	virtual void 除算演算子を書く  () = 0;
	// write addition operator
	virtual void 加算演算子を書く  () = 0;
	// write subtraction operator
	virtual void 減算演算子を書く  () = 0;
};

// scan next token
Token 次の字句を得る(InfixReader& input)
{
	switch (input.今見ている文字を読む()) {
		//定数・ゼロの考慮が書けていました。申し訳ありません
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
				(value *= 10) += input.今見ている文字を読む() - '0';
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
Token 加減算式を処理する(InfixReader& input, Token 解析対象字句, PostfixWriter& output);

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
// convert notation from infix to postfix
void 中置記法から後置記法に変換する(InfixReader& input, PostfixWriter& output)
{
	加減算式を処理する(input, 次の字句を得る(input), output);
}
#include <sstream>
class InfixReader_string : public InfixReader {
	std::istringstream istm;
	char               ch  ;

	static char ReadNextCharacter(std::istream& istm)
	{
		char ch;
		if (istm.read(&ch, 1))
			return ch;
		else
			return '\0';
	}

	int 今見ている文字を読む   () override
	{
		return ch;
	}
	int 次の文字を読む         () override
	{
		return ch = ReadNextCharacter(istm);
	}
public:
	InfixReader_string(const char* s)
		: istm{ s                       }
		, ch  { ReadNextCharacter (istm)}
	{
	}
};
#include <iostream>
class PostfixWriter_cout : public PostfixWriter {
	void 定数を書く(int value) override
	{
		std::cout << "定数：" << value << '\n';
	}
	void 単項マイナスを書く() override
	{
		std::cout << "単項演算子：-\n";
	}
	void 乗算演算子を書く  () override
	{
		std::cout << "二項演算子：*\n";
	}
	void 除算演算子を書く  () override
	{
		std::cout << "二項演算子：/\n";
	}
	void 加算演算子を書く  () override
	{
		std::cout << "二項演算子：+\n";
	}
	void 減算演算子を書く  () override
	{
		std::cout << "二項演算子：-\n";
	}
};
#include <array>
int main()
{
	中置記法から後置記法に変換する
	( std::array<InfixReader_string, 1>{ "5*6-(-6)*8" }.front()
	, std::array<PostfixWriter_cout, 1>{              }.front()
	);
}
/*
--------
関連質問
--------
https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q13270550353
1251354923さん

2022/11/5 3:47

unary operatorの識別方法

文字列に数式が入力されてるとき
例
5*6-(-6)*8
こののち、unary operatorの-を#として、後置法で出力させたいです。
どうやってunary operatorの-を識別するのか、

C言語関連・2閲覧
*/
