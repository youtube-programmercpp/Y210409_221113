// 受領日：2022/11/13(日)
// 作成者：GoldSmith さん
// 備考：名前空間の作成とファイル分割（ヘッダファイル作成）は当方にて行いました。
#pragma once
#include <Windows.h>
#include <string>
namespace Trial_A {
	using namespace std;
	void DrawBlue(const basic_string<TCHAR>& str, const PAINTSTRUCT& ps);
}
