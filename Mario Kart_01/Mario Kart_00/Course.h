#pragma once
class Player;


class Course {
public:
	//コンストラクタ
	Course();
	//デストラクタ
	~Course();
	//初期化。
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//更新。
	void Update();
	//描画。
	void Course::Render(
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight
		);
	//開放。
	void Release();
	//座標を設定。
	void SetPosition(D3DXVECTOR3 pos);
	void IsIntersect(D3DXVECTOR3 pos, D3DXVECTOR3 ray, int*isHit, float*len);
	D3DXVECTOR3 GetPosition()
	{
		return position;
	}
	D3DXVECTOR3 GetRay()
	{
		return rayInGround;
	}
	Player *player;
private:
	D3DXVECTOR3				position;		//座標。
	LPD3DXMESH				mesh;			//メッシュ。
	LPDIRECT3DTEXTURE9*		textures;		//テクスチャ。
	DWORD					numMaterial;	//マテリアルの数。
	ID3DXEffect*			effect;			//エフェクト。
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXMATRIX				mRotation;		//回転行列。
	D3DXMATRIX				worldInvr;		//ワールド行列の逆行列
	D3DXVECTOR3				rayInGround;	//レイ
};