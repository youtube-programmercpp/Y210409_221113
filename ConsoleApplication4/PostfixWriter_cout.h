// C++サンプルプログラム（ファイル分割例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#pragma once
#include "PostfixWriter.h"
class PostfixWriter_cout : public PostfixWriter {
	void 定数を書く(int value) override;
	void 単項マイナスを書く() override;
	void 乗算演算子を書く  () override;
	void 除算演算子を書く  () override;
	void 加算演算子を書く  () override;
	void 減算演算子を書く  () override;
};
