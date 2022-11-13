// 受領日：2022/11/13(日)
// 作成者：GoldSmith さん
// 備考：名前空間の作成とファイル分割（ヘッダファイル作成）は当方にて行いました。
#include "pch.h"
#include "DrawBlue.h"
#include "Draw.h"

void Trial_A::DrawBlue(const basic_string<TCHAR>& str, const PAINTSTRUCT& ps)
{
	COLORREF DefCol = GetTextColor(ps.hdc);
	SetTextColor(ps.hdc, RGB(0, 127, 127));
	Draw(str, ps);
	SetTextColor(ps.hdc, DefCol);
}
