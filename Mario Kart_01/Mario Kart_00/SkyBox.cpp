#include "stdafx.h"
#include "SkyBox.h"

//�R���X�g���N�^
SkyBox::SkyBox()
{
	//�������B
	mesh = NULL;
	textures = NULL;
	numMaterial = 0;
	effect = NULL;
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixIdentity(&mRotation);
	position.x = 0.0f;
	position.y = -130.0f;
	position.z = 0.0f;
}
//�f�X�g���N�^H
SkyBox::~SkyBox()
{  
	Release();
}
//���W��ݒ�B
void SkyBox::SetPosition(D3DXVECTOR3 pos)
{
	position = pos;
}
//�������B
void SkyBox::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	//X�t�@�C�������[�h�B
	LPD3DXBUFFER pD3DXMtrlBuffer;
	//X�t�@�C���̃��[�h�B
	D3DXLoadMeshFromX("sky.x", D3DXMESH_SYSTEMMEM,
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
	// �}�e���A���o�b�t�@������B
	pD3DXMtrlBuffer->Release();

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
}
//�X�V�B
void SkyBox::Update()
{
	//���[���h�s��̍X�V�B
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
	D3DXMATRIX mScale;
	D3DXMatrixScaling(&mScale, 4.0f, 4.0f, 4.0f);
	mWorld = mScale * mWorld;
}
//�`��B
void SkyBox::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
	)
{
	effect->SetTechnique("SkinModel");
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



	for (DWORD i = 0; i < numMaterial; i++)
	{
		effect->SetTexture("g_diffuseTexture", textures[i]);
		effect->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
		// Draw the mesh subset
		mesh->DrawSubset(i);
	}

	effect->EndPass();
	effect->End();
}
//�J���B
void SkyBox::Release()
{
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