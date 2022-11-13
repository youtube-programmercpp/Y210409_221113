// C++サンプルプログラム（ファイル分割例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#include "InfixReader_string.h"

char InfixReader_string::ReadNextCharacter(std::istream& istm)
{
	char ch;
	if (istm.read(&ch, 1))
		return ch;
	else
		return '\0';
}
int InfixReader_string::今見ている文字を読む   ()
{
	return ch;
}
int InfixReader_string::次の文字を読む         ()
{
	return ch = ReadNextCharacter(istm);
}
InfixReader_string::InfixReader_string(const char* s)
	: istm{ s                       }
	, ch  { ReadNextCharacter (istm)}
{
}
