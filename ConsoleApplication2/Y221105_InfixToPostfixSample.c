// C言語サンプルプログラム：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
enum TokenCategory
{ token_不明な文字   // unknown character
, token_正の整数定数 // positive integer constant
, token_プラス       // '+' plus
, token_マイナス     // '-' minus
, token_アスタリスク // '*' asterisk
, token_スラッシュ   // '/' slash
, token_左括弧       // '(' left parenthesis
, token_右括弧       // ')' right parenthesis
};
struct Token {
	enum TokenCategory  字句の種類; //category
	int                 定数値    ; //value   
};

struct InfixReader;
// read current character
int 今見ている文字を読む   (struct InfixReader* input);
// read next character
int 次の文字を読む         (struct InfixReader* input);

struct PostfixWriter;
// write constant
void 定数を書く        (struct PostfixWriter* output, int value);
// write unary minus operator
void 単項マイナスを書く(struct PostfixWriter* output);
// write multiplication operator
void 乗算演算子を書く  (struct PostfixWriter* output);
// write division operator
void 除算演算子を書く  (struct PostfixWriter* output);
// write addition operator
void 加算演算子を書く  (struct PostfixWriter* output);
// write subtraction operator
void 減算演算子を書く  (struct PostfixWriter* output);

#ifdef __cplusplus
#	define	字句オブジェクト
#else
#	define	字句オブジェクト (struct Token)
#endif

// scan next token
struct Token 次の字句を得る(struct InfixReader* input)
{
	//数字列を読み取る
	//先頭に 0～9、その後 0 個以上の数字が続く
	switch (今見ている文字を読む(input)) {
	case '0'://0が単体（定数ゼロの考慮が抜けていました。） PENDING
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		for (int value = 今見ている文字を読む(input) - '0';;) {
			switch (次の文字を読む(input)) {
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
				value += 今見ている文字を読む(input) - '0';
				continue;
			default:
				return 字句オブジェクト{ token_正の整数定数, value };
			}
		}
	case '+' : 次の文字を読む(input); return 字句オブジェクト{ token_プラス       };
	case '-' : 次の文字を読む(input); return 字句オブジェクト{ token_マイナス     };
	case '*' : 次の文字を読む(input); return 字句オブジェクト{ token_アスタリスク };
	case '/' : 次の文字を読む(input); return 字句オブジェクト{ token_スラッシュ   };
	case '(' : 次の文字を読む(input); return 字句オブジェクト{ token_左括弧       };
	case ')' : 次の文字を読む(input); return 字句オブジェクト{ token_右括弧       };
	default:
		return 字句オブジェクト { token_不明な文字 };
	}
}
struct Token 加減算式を処理する(struct InfixReader* input, struct Token 解析対象字句, struct PostfixWriter* output);

//parse primary expression
struct Token 一次式を処理する(struct InfixReader* input, struct Token 解析対象字句, struct PostfixWriter* output)
{
	switch (解析対象字句.字句の種類) {
	case token_左括弧:
		解析対象字句 = 加減算式を処理する(input, 次の字句を得る(input), output);
		if (解析対象字句.字句の種類 == token_右括弧)
			return 次の字句を得る(input);
		else
			return 字句オブジェクト{ token_不明な文字 };
	case token_正の整数定数:
		定数を書く(output, 解析対象字句.定数値);
		return 次の字句を得る(input);
	default:
		return 字句オブジェクト{ token_不明な文字 };
	}
}
//parse unary expression
struct Token 単項式を処理する(struct InfixReader* input, struct Token 解析対象字句, struct PostfixWriter* output)
{
	switch (解析対象字句.字句の種類) {
	case token_プラス  : 解析対象字句 = 単項式を処理する(input, 次の字句を得る(input), output);                             return 解析対象字句;
	case token_マイナス: 解析対象字句 = 単項式を処理する(input, 次の字句を得る(input), output); 単項マイナスを書く(output); return 解析対象字句;
	default:
		return 一次式を処理する(input, 解析対象字句, output);
	}
}
//parse multiplicative expression
struct Token 乗除算式を処理する(struct InfixReader* input, struct Token 解析対象字句, struct PostfixWriter* output)
{
	解析対象字句 = 単項式を処理する(input, 解析対象字句, output);
	for (;;) {
		switch (解析対象字句.字句の種類) {
		case token_アスタリスク: 解析対象字句 = 単項式を処理する(input, 次の字句を得る(input), output); 乗算演算子を書く(output); continue;
		case token_スラッシュ  : 解析対象字句 = 単項式を処理する(input, 次の字句を得る(input), output); 除算演算子を書く(output); continue;
		default:
			return 解析対象字句;
		}
	}
}
//parse additive expression
struct Token 加減算式を処理する(struct InfixReader* input, struct Token 解析対象字句, struct PostfixWriter* output)
{
	for (解析対象字句 = 乗除算式を処理する(input, 解析対象字句, output);;) {
		switch (解析対象字句.字句の種類) {
		case token_プラス  : 解析対象字句 = 乗除算式を処理する(input, 次の字句を得る(input), output); 加算演算子を書く(output); continue;
		case token_マイナス: 解析対象字句 = 乗除算式を処理する(input, 次の字句を得る(input), output); 減算演算子を書く(output); continue;
		default:
			return 解析対象字句;
		}
	}
}
// convert notation from infix to postfix
void 中置記法から後置記法に変換する(struct InfixReader* input, struct PostfixWriter* output)
{
	加減算式を処理する(input, 次の字句を得る(input), output);
}

struct InfixReader {
	const char* s;
};
int 今見ている文字を読む   (struct InfixReader* input)
{
	return *input->s;
}
int 次の文字を読む         (struct InfixReader* input)
{
	if (*input->s)
		return *++input->s;
	else
		return '\0';

}

#include <stdio.h>
struct PostfixWriter {
	FILE* fp;
};
void 定数を書く(struct PostfixWriter* output, int value)
{
	fprintf(output->fp, "定数：%d\n", value);
}
void 単項マイナスを書く(struct PostfixWriter* output)
{
	fprintf(output->fp, "単項演算子：-\n");
}
void 乗算演算子を書く  (struct PostfixWriter* output)
{
	fprintf(output->fp, "二項演算子：*\n");
}
void 除算演算子を書く  (struct PostfixWriter* output)
{
	fprintf(output->fp, "二項演算子：/\n");
}
void 加算演算子を書く  (struct PostfixWriter* output)
{
	fprintf(output->fp, "二項演算子：+\n");
}
void 減算演算子を書く  (struct PostfixWriter* output)
{
	fprintf(output->fp, "二項演算子：-\n");
}

int main()
{
	struct InfixReader reader = { "5*6-(-6)*8" };
	struct PostfixWriter writer = { stdout };
	中置記法から後置記法に変換する(&reader, &writer);
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
