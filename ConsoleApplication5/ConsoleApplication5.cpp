// C++サンプルプログラム（DLL化使用例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#include "../Dll1/InfixReader.h"
#include "../Dll1/PostfixWriter.h"
#include "../Dll1/InfixToPostfixConverter.h"
#pragma comment(lib, "Dll1")

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
