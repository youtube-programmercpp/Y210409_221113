// 受領日：2022/11/13(日)
// 作成者：GoldSmith さん
// 備考：名前空間の作成とファイル分割（ヘッダファイル作成）は当方にて行いました。
#include "pch.h"
#include "ParseStr.h"
#include "Draw.h"
#include "ConvAndDraw.h"
#include <tchar.h>

void Trial_A::ParseStr(basic_string<TCHAR> const& str, const size_t pos, const PAINTSTRUCT& ps)
{
	const basic_string<TCHAR> EscCode(_T("\x1b\r\n"));
	const size_t fpos = str.find_first_of(EscCode, pos);
	if (fpos == basic_string<TCHAR>::npos)
	{
		Draw(str.substr(pos, str.size() - pos), ps);
		return;
	}
	Draw(str.substr(pos, fpos - pos), ps);
	ConvAndDraw(str.at(fpos), fpos, ps);
	if (fpos + 1 == basic_string<TCHAR>::npos)
	{
		return;
	}
	ParseStr(str, fpos + 1, ps);
	return;
}
