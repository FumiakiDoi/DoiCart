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
		g_pd3dDevice,				// Direct3D�f�o�C�X
		24,						// ����
		10,						// ��
		FW_REGULAR,				// �t�H���g�̑��� ����
		NULL,					// ����
		FALSE,					// �Α�
		SHIFTJIS_CHARSET,		// �����Z�b�g
		OUT_DEFAULT_PRECIS,		// �o�͐��x�͕���
		PROOF_QUALITY,			// �����i�����d��
		FIXED_PITCH | FF_SCRIPT,	// �s�b�`�ƃt�@�~��
		TEXT("�l�r�@�o�S�V�b�N"),	// �t�H���g��
		&pFont);					// ID3DXFont�|�C���^
}

void Text::Render()  
{
	
	sprintf(text1, "%.0f km/h\n",D3DXVec3Length(&game->GetPlayer()->GetMeter()));
	 
	RECT rc = {
		0,		// �����x���W
		0,		// �����y���W
		640,	// �E����x���W
		24		// �E����y���W
	};
	// �`��
	pFont->DrawText(
		NULL,							// NULL
		text1,							// �`��e�L�X�g
		-1,								// �S�ĕ\��
		&rc,							// �\���͈�
		DT_LEFT,						// ����
		D3DCOLOR_XRGB(0, 0, 0)	// ���F
		);
}