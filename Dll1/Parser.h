// C++サンプルプログラム（DLL化実装例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#pragma once
struct Token;
struct InfixReader;
struct PostfixWriter;
Token 加減算式を処理する(InfixReader& input, Token 解析対象字句, PostfixWriter& output);
