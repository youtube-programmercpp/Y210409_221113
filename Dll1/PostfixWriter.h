// C++サンプルプログラム（DLL化実装例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#pragma once
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
