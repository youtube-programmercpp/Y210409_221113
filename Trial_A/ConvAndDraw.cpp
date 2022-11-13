// 受領日：2022/11/13(日)
// 作成者：GoldSmith さん
// 備考：名前空間の作成とファイル分割（ヘッダファイル作成）は当方にて行いました。
#include "pch.h"
#include "ConvAndDraw.h"
#include "DrawBlue.h"
#include <tchar.h>
#include <map>

void Trial_A::ConvAndDraw(const TCHAR ch, const size_t pos, const PAINTSTRUCT& ps)
{
	map<TCHAR, basic_string<TCHAR>> mapCode =
	{ {_T('\x1b'),_T("ESC")},{_T('\r'),_T("\\r")},{_T('\n'),_T("\\n")} };
	basic_string<TCHAR> strCode(mapCode.at(ch));
	DrawBlue(strCode, ps);
}
