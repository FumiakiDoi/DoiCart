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
	D3DXMatrixIdentity(&mRot);
	pD3DXMtrlBuffer = NULL;
	accel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	brake = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	moveDirection = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	frg = false;
}
//�f�X�g���N�^H
Player::~Player()
{
	Release();
}

//�������B
void Player::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	//X�t�@�C���̃��[�h�B
	D3DXLoadMeshFromX("car.x", D3DXMESH_SYSTEMMEM,
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
	if (D3DXVec3Length(&speed) > 0.1f)
	{

		float xstick = game->Getpat()->GetLStickXF();
		{
			D3DXMATRIX kaiten;
			D3DXMatrixRotationY(&kaiten, TurnSpeed *xstick);
			D3DXVECTOR4 vOut;
			D3DXVECTOR4 vSpeed;
			D3DXVec3Transform(&vOut, &moveDirection, &kaiten);//move��kaiten�̌v�Z���ʂ�Out�ɓ���
			D3DXVec3Transform(&vSpeed, &speed, &kaiten);
			if (!game->Getpat()->IsPress(enButtonRB1))
			{
				moveDirection.x = vOut.x;
				moveDirection.y = vOut.y;
				moveDirection.z = vOut.z;
				speed.x = vSpeed.x;
				speed.y = vSpeed.y;
				speed.z = vSpeed.z;
				mRot = mRot * kaiten;
			}
			else
			{
				moveDirection.x = vOut.x;
				moveDirection.y = vOut.y;
				moveDirection.z = vOut.z;
				mRot = mRot * kaiten;
			}
		}
	}

	
	//�A�N�Z���ƃu���[�L
	/*if (GetAsyncKeyState('A'))
	{
		accel = moveDirection * ACCEL;
	}else if (GetAsyncKeyState('S'))
	{*/
	if (game->Getpat()->IsPress(enButtonA))
	{
		accel = moveDirection * ACCEL;
	}
	else if (game->Getpat()->IsPress(enButtonB))
	{
		if (D3DXVec3Length(&speed)<0.1f)
		{
			accel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			//�u���[�L
			accel = moveDirection * BRAKE;
			//accel = D3DXVECTOR3(0.0f, 0.0f, -10.0f);
		}
	}
	else
	{
		if (D3DXVec3Length(&speed) < 0.1f)
		{
			accel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			//�G���W���u���[�L
			accel = moveDirection * ANZINBRAKE;
			//accel = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		}
	}
	
	
	//accel *= 0.016666666666f;
	//���̃t���[���ŉ������鑬�x���v�Z����B
	D3DXVECTOR3 addSpeed;
	addSpeed = accel * (1.0f / 60.0f);
	speed += addSpeed;

	//brake
	D3DXVECTOR3 addbrake;
	addbrake = accel * (1.0f / 60.0f);
	brake -= addbrake;

	//���̃t���[���ňړ���������W���v�Z����B
	D3DXVECTOR3 addPosition;
	addPosition = speed * (1.0f / 60.0f);
	position += addPosition;
	int						isHit;			//�����������ǂ������L�^
	float					Len;
	D3DXVECTOR3 posrocal;
	posrocal = position;
	posrocal.y += 2.0f;
	course->IsIntersect(posrocal, D3DXVECTOR3(0.0f, -1.0f, 0.0f),&isHit,&Len);
	D3DXMatrixTranslation(&mTrans, position.x, position.y, position.z);
	if (isHit==false)
	{
		position.y -= 0.1f;
	}
	if (position.y < -10)
	{
		position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	//D3DXMatrixRotationY(&mRot, currentAngleY);
	mWorld =mRot * mTrans;


	speedMeter = speed;
	speedMeter *= 60;
	speedMeter *= 60;
	speedMeter /= 1000;
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

	effect->SetMatrix("g_rotationMatrix", &mRot);		//��]�s���]���B
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