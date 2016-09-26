#pragma once
#define ACCEL 4
#define BRAKE -10
#define ANZINBRAKE -1
#include "Course.h"


class Player {
public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();
	//�������B
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//�X�V�B
	void Update();
	//�`��B
	void Player::Render(
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight
		);
	//�J���B
	void Release();
	//���W��ݒ�B
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
	
	D3DXMATRIX				mTrans;			//���s�ړ��s����쐬����B
	D3DXMATRIX				mRot;			//��]�s����쐬����B
	D3DXVECTOR3				position;		//���W�B
	D3DXQUATERNION			rotation;		//��]
	LPD3DXMESH				mesh;			//���b�V���B
	LPDIRECT3DTEXTURE9*		textures;		//�e�N�X�`���B
	DWORD					numMaterial;	//�}�e���A���̐��B
	ID3DXEffect*			effect;			//�G�t�F�N�g�B
	D3DXMATRIX				mWorld;			//���[���h�s��B
	LPD3DXBUFFER			pD3DXMtrlBuffer;	//�}�e���A���o�b�t�@
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