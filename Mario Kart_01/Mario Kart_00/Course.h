#pragma once
class Player;


class Course {
public:
	//�R���X�g���N�^
	Course();
	//�f�X�g���N�^
	~Course();
	//�������B
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//�X�V�B
	void Update();
	//�`��B
	void Course::Render(
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
	D3DXVECTOR3				position;		//���W�B
	LPD3DXMESH				mesh;			//���b�V���B
	LPDIRECT3DTEXTURE9*		textures;		//�e�N�X�`���B
	DWORD					numMaterial;	//�}�e���A���̐��B
	ID3DXEffect*			effect;			//�G�t�F�N�g�B
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXMATRIX				mRotation;		//��]�s��B
	D3DXMATRIX				worldInvr;		//���[���h�s��̋t�s��
	D3DXVECTOR3				rayInGround;	//���C
};