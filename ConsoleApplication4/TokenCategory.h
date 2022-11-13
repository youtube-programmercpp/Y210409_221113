// C++サンプルプログラム（ファイル分割例）：中置記法から後置記法への変換 Copyright(C) 2022 https://www.youtube.com/@ProgrammerCpp
#pragma once
enum class TokenCategory
{ 不明な文字   // unknown character
, 正の整数定数 // positive integer constant
, プラス       // '+' plus
, マイナス     // '-' minus
, アスタリスク // '*' asterisk
, スラッシュ   // '/' slash
, 左括弧       // '(' left parenthesis
, 右括弧       // ')' right parenthesis
};
