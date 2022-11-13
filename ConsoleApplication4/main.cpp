// C++サンプルプログラム（ファイル分割例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#include "InfixToPostfixConverter.h"
#include "InfixReader_string.h"
#include "PostfixWriter_cout.h"
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
