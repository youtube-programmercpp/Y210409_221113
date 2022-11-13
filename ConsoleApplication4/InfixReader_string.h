// C++サンプルプログラム（ファイル分割例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#pragma once
#include "InfixReader.h"
#include <sstream>
class InfixReader_string : public InfixReader {
	std::istringstream istm;
	char               ch  ;

	static char ReadNextCharacter(std::istream& istm);

	int 今見ている文字を読む   () override;
	int 次の文字を読む         () override;
public:
	InfixReader_string(const char* s);
};
