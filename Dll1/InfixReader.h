// C++サンプルプログラム（DLL化実装例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#pragma once
struct InfixReader {
	// read current character
	virtual int 今見ている文字を読む   () = 0;
	// read next character
	virtual int 次の文字を読む         () = 0;
};
