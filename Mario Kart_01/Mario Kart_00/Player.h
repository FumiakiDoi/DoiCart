#pragma once
#define ACCEL 4
#define BRAKE -10
#define ANZINBRAKE -1
#include "Course.h"


class Player {
public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();
	//初期化。
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//更新。
	void Update();
	//描画。
	void Player::Render(
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
	const D3DXVECTOR3& GetPosition() const
	{
		return position;
	}
	D3DXVECTOR3& GetDirection()
	{
		return moveDirection;
	}
	D3DXVECTOR3& GetMeter()
	{
		return speedMeter;
	}
	Course *course;

private:
	
	D3DXMATRIX				mTrans;			//平行移動行列を作成する。
	D3DXMATRIX				mRot;			//回転行列を作成する。
	D3DXVECTOR3				position;		//座標。
	D3DXQUATERNION			rotation;		//回転
	LPD3DXMESH				mesh;			//メッシュ。
	LPDIRECT3DTEXTURE9*		textures;		//テクスチャ。
	DWORD					numMaterial;	//マテリアルの数。
	ID3DXEffect*			effect;			//エフェクト。
	D3DXMATRIX				mWorld;			//ワールド行列。
	LPD3DXBUFFER			pD3DXMtrlBuffer;	//マテリアルバッファ
	float					currentAngleY = 0.0f;
	float					targetAngleY = 0.0f;
	const float				TurnSpeed = D3DXToRadian(0.8f);
	float					turnSpeed = 0.0f;
	bool					frg;
	D3DXVECTOR3				accel;
	D3DXVECTOR3				speed;
	D3DXVECTOR3				brake;
	D3DXVECTOR3				moveDirection;
	D3DXVECTOR3				speedMeter;
};