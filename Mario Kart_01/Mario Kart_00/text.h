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
	LPD3DXFONT				pFont;	// フォントオブジェクト
	char text1[256];
};

