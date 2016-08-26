#include "stdafx.h"
#include "Player.h"
#include "Game.h"


//�R���X�g���N�^
Player::Player()
{
	//�������B
	mesh = NULL;
	textures = NULL;
	numMaterial = 0;
	effect = NULL;
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixIdentity(&mRotation);
	/*position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
	rotation.x = 0.0f;
	rotation.y = 0.0f;
	rotation.z = 0.0f;*/
	pD3DXMtrlBuffer = NULL;
	accel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//�f�X�g���N�^H
Player::~Player()
{
	Release();
}
//���W��ݒ�B
void Player::SetPosition(D3DXVECTOR3 pos)
{
	position = pos;
}
//�������B
void Player::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	//X�t�@�C���̃��[�h�B
	D3DXLoadMeshFromX("BMWPlayer.x", D3DXMESH_SYSTEMMEM,
		pd3dDevice, NULL,
		&pD3DXMtrlBuffer, NULL, &numMaterial,
		&mesh);
	// �}�e���A���o�b�t�@���擾�B
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	//�e�N�X�`�������[�h�B
	textures = new LPDIRECT3DTEXTURE9[numMaterial];
	for (DWORD i = 0; i < numMaterial; i++)
	{
		textures[i] = NULL;
		//�e�N�X�`�����쐬����B
		D3DXCreateTextureFromFileA(pd3dDevice,
			d3dxMaterials[i].pTextureFilename,
			&textures[i]);
	}
	

	//�V�F�[�_�[���R���p�C���B
	LPD3DXBUFFER  compileErrorBuffer = NULL;
	//�V�F�[�_�[���R���p�C���B
	HRESULT hr = D3DXCreateEffectFromFile(
		pd3dDevice,
		"basic.fx",
		NULL,
		NULL,
		D3DXSHADER_SKIPVALIDATION,
		NULL,
		&effect,
		&compileErrorBuffer
		);
	if (hr != S_OK) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}
//�X�V�B
void Player::Update()
{
	bool isTurn = false;
	const float moveSpeed = 0.3;
	D3DXVECTOR3 moveDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if(GetAsyncKeyState(VK_UP))
	{
		position.z += moveSpeed;
		//moveDir -= direction_z;
		currentAngleY = D3DXToRadian(0.0f);
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		position.z -= moveSpeed;
		//moveDir += direction_z;
		currentAngleY = D3DXToRadian(180.0f);
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		//Y += D3DXToRadian(1.0f);
		//position.x += 0.1f;
		currentAngleY = D3DXToRadian(90.0f);
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		//position.x -= 0.1f;
		//moveDir -= direction_x;
		currentAngleY = D3DXToRadian(-90.0f);
	}
	if (GetAsyncKeyState('A'))
	{
		accel = D3DXVECTOR3(0.0f, 0.0f, 10.0f);
	}
	
	//accel *= 0.016666666666f;
	//���̃t���[���ŉ������鑬�x���v�Z����B
	D3DXVECTOR3 addSpeed;
	addSpeed = accel * (1.0f/60.0f);
	speed += addSpeed;

	//���̃t���[���ňړ���������W���v�Z����B
	D3DXMatrixTranslation(&mTrans, position.x, position.y, position.z);
	D3DXMatrixRotationY(&mRot, currentAngleY);
	mWorld = mRot * mTrans;

}
//�`��B
void Player::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
	)
{
	effect->SetTechnique("SkinModelTexture");
	effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	effect->BeginPass(0);
	
	//�萔���W�X�^�ɐݒ肷��J���[�B
	D3DXVECTOR4 color(1.0f, 0.0f, 0.0f, 1.0f);
	//���[���h�s��̓]���B
	effect->SetMatrix("g_worldMatrix", &mWorld);
	//�r���[�s��̓]���B
	effect->SetMatrix("g_viewMatrix", &viewMatrix);			//�r���[�s���]���B

	effect->SetMatrix("g_projectionMatrix", &projMatrix);	//�v���W�F�N�V�����s��̓]���B

	effect->SetMatrix("g_rotationMatrix", &mRotation);		//��]�s���]���B
	//���C�g�̌�����]���B
	effect->SetVectorArray("g_diffuseLightDirection", diffuseLightDirection, numDiffuseLight);
	//���C�g�̃J���[��]���B
	effect->SetVectorArray("g_diffuseLightColor", diffuseLightColor, numDiffuseLight);
	//������ݒ�B
	effect->SetVector("g_ambientLight", &ambientLight);

	
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	for (DWORD i = 0; i < numMaterial; i++)
	{
		effect->SetTexture("g_diffuseTexture", textures[i]);
		
		effect->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
		// Draw the mesh su{bset
		mesh->DrawSubset(i);
	}

	effect->EndPass();
	effect->End();
}
//�J���B
void Player::Release()
{
	// �}�e���A���o�b�t�@������B
	if (pD3DXMtrlBuffer != NULL){
		pD3DXMtrlBuffer->Release();
		pD3DXMtrlBuffer = NULL;
	}
	
	//���b�V�����J���B
	if (mesh != NULL) {
		mesh->Release();
		mesh = NULL;
	}
	//�e�N�X�`�����J���B
	if (textures != NULL) {
		for (unsigned int i = 0; i < numMaterial; i++) {
			if (textures[i] != NULL) {
				textures[i]->Release();
				textures[i] = NULL;
			}
		}
		delete[] textures;
		textures = NULL;
	}
	//�G�t�F�N�g���J���B
	if (effect != NULL) {
		effect->Release();
		effect = NULL;
	}
}