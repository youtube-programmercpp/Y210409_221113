// C++サンプルプログラム（DLL応用・計算実行処理例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
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
#include <list>
class PostfixWriter_calc : public PostfixWriter {
	std::list<int> stack;
	void 定数を書く(int value) override
	{
		stack.push_back(value);
	}
	void 単項マイナスを書く() override
	{
		stack.back() *= -1;
	}
	void 乗算演算子を書く  () override
	{
		const auto right = stack.back();
		stack.pop_back();
		stack.back() *= right;
	}
	void 除算演算子を書く  () override
	{
		const auto right = stack.back();
		stack.pop_back();
		stack.back() /= right;
	}
	void 加算演算子を書く  () override
	{
		const auto right = stack.back();
		stack.pop_back();
		stack.back() += right;
	}
	void 減算演算子を書く  () override
	{
		const auto right = stack.back();
		stack.pop_back();
		stack.back() -= right;
	}
public:
	explicit operator bool() const noexcept
	{
		return stack.size() == 1;
	}
	int 計算結果() const noexcept
	{
		return stack.back();
	}
	void リセット() noexcept
	{
		stack.clear();
	}
};
#include <array>
#include <iostream>
int main()
{
	PostfixWriter_calc 計算器;
	中置記法から後置記法に変換する(std::array<InfixReader_string, 1>{ "5*6-(-6)*8" }.front(), 計算器);
	if (計算器)
		std::cout << "計算結果：" << 計算器.計算結果() << '\n';
	計算器.リセット();
	std::string s;
	if (std::getline(std::cin, s)) {
		中置記法から後置記法に変換する(std::array<InfixReader_string, 1>{ s.c_str() }.front(), 計算器);
		if (計算器)
			std::cout << "計算結果：" << 計算器.計算結果() << '\n';
	}
}
