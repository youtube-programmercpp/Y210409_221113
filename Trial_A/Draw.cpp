// 受領日：2022/11/13(日)
// 作成者：GoldSmith さん
// 備考１：名前空間の作成とファイル分割（ヘッダファイル作成）は当方にて行いました。
// 備考２：static_cast<UINT> のキャストは当方で追加しました。
#include "pch.h"
#include "Draw.h"

void Trial_A::Draw(const basic_string<TCHAR>& tstr, const PAINTSTRUCT& ps)
{
	ExtTextOut(ps.hdc
		, 0
		, 0
		, ETO_CLIPPED
		, &ps.rcPaint
		, tstr.data()
		, /*_In_ UINT c*/static_cast<UINT>(tstr.size())
		, NULL);
}
