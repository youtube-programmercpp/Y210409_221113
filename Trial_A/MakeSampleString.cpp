// 受領日：2022/11/13(日)
// 作成者：GoldSmith さん
// 備考：文字列作成関数として当方の判断で独立させました
#include "pch.h"
#include "MakeSampleString.h"
#include <tchar.h>
std::basic_string<TCHAR> Trial_A::MakeSampleString()
{
	//対象の文字列
	return _T("\x1b[2JHellow\r\n");
}
