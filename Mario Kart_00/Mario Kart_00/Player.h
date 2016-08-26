#pragma once




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
	D3DXMATRIX				mRotation;		//��]�s��B
	LPD3DXBUFFER			pD3DXMtrlBuffer;	//�}�e���A���o�b�t�@
	D3DXVECTOR3				direction_z;	//�v���C���[��Z�����B
	D3DXVECTOR3				direction_x;	//�v���C���[��X�����B
	float					currentAngleY = 0.0f;
	float					targetAngleY = 0.0f;
	const float				cTurnSpeed = D3DXToRadian(10.0f);
	float					turnSpeed = 0.0f;
	D3DXVECTOR3				accel;
	D3DXVECTOR3				speed;
};