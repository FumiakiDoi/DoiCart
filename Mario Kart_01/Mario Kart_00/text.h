#pragma once



class Text {
public:
	Text();
	~Text();
	void Init();
	void Update();
	void Render();
	void Release();
private:
	LPD3DXFONT				pFont;	// �t�H���g�I�u�W�F�N�g
	char text1[256];
};

