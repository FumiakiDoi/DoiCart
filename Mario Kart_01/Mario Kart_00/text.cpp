#include "stdafx.h"
#include <strsafe.h>
#include <d3dx9effect.h>
#include "text.h"
#include "System.h"
#include "Game.h"




Text::Text()
{

}
Text::~Text()
{

}


void Text::Init()
{
	D3DXCreateFont(
		g_pd3dDevice,				// Direct3Dデバイス
		24,						// 高さ
		10,						// 幅
		FW_REGULAR,				// フォントの太さ 普通
		NULL,					// 下線
		FALSE,					// 斜体
		SHIFTJIS_CHARSET,		// 文字セット
		OUT_DEFAULT_PRECIS,		// 出力制度は普通
		PROOF_QUALITY,			// 文字品質を重視
		FIXED_PITCH | FF_SCRIPT,	// ピッチとファミリ
		TEXT("ＭＳ　Ｐゴシック"),	// フォント名
		&pFont);					// ID3DXFontポインタ
}

void Text::Render()  
{
	
	sprintf(text1, "%.0f km/h\n",D3DXVec3Length(&game->GetPlayer()->GetMeter()));
	 
	RECT rc = {
		0,		// 左上のx座標
		0,		// 左上のy座標
		640,	// 右下のx座標
		24		// 右下のy座標
	};
	// 描画
	pFont->DrawText(
		NULL,							// NULL
		text1,							// 描画テキスト
		-1,								// 全て表示
		&rc,							// 表示範囲
		DT_LEFT,						// 左寄せ
		D3DCOLOR_XRGB(0, 0, 0)	// 白色
		);
}