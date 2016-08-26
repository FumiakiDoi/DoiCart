#include "stdafx.h"
#include "Player.h"
#include "Game.h"


//コンストラクタ
Player::Player()
{
	//初期化。
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
//デストラクタH
Player::~Player()
{
	Release();
}
//座標を設定。
void Player::SetPosition(D3DXVECTOR3 pos)
{
	position = pos;
}
//初期化。
void Player::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	//Xファイルのロード。
	D3DXLoadMeshFromX("BMWPlayer.x", D3DXMESH_SYSTEMMEM,
		pd3dDevice, NULL,
		&pD3DXMtrlBuffer, NULL, &numMaterial,
		&mesh);
	// マテリアルバッファを取得。
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	//テクスチャをロード。
	textures = new LPDIRECT3DTEXTURE9[numMaterial];
	for (DWORD i = 0; i < numMaterial; i++)
	{
		textures[i] = NULL;
		//テクスチャを作成する。
		D3DXCreateTextureFromFileA(pd3dDevice,
			d3dxMaterials[i].pTextureFilename,
			&textures[i]);
	}
	

	//シェーダーをコンパイル。
	LPD3DXBUFFER  compileErrorBuffer = NULL;
	//シェーダーをコンパイル。
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
//更新。
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
	//このフレームで加速する速度を計算する。
	D3DXVECTOR3 addSpeed;
	addSpeed = accel * (1.0f/60.0f);
	speed += addSpeed;

	//このフレームで移動させる座標を計算する。
	D3DXMatrixTranslation(&mTrans, position.x, position.y, position.z);
	D3DXMatrixRotationY(&mRot, currentAngleY);
	mWorld = mRot * mTrans;

}
//描画。
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
	
	//定数レジスタに設定するカラー。
	D3DXVECTOR4 color(1.0f, 0.0f, 0.0f, 1.0f);
	//ワールド行列の転送。
	effect->SetMatrix("g_worldMatrix", &mWorld);
	//ビュー行列の転送。
	effect->SetMatrix("g_viewMatrix", &viewMatrix);			//ビュー行列を転送。

	effect->SetMatrix("g_projectionMatrix", &projMatrix);	//プロジェクション行列の転送。

	effect->SetMatrix("g_rotationMatrix", &mRotation);		//回転行列を転送。
	//ライトの向きを転送。
	effect->SetVectorArray("g_diffuseLightDirection", diffuseLightDirection, numDiffuseLight);
	//ライトのカラーを転送。
	effect->SetVectorArray("g_diffuseLightColor", diffuseLightColor, numDiffuseLight);
	//環境光を設定。
	effect->SetVector("g_ambientLight", &ambientLight);

	
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	for (DWORD i = 0; i < numMaterial; i++)
	{
		effect->SetTexture("g_diffuseTexture", textures[i]);
		
		effect->CommitChanges();						//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
		// Draw the mesh su{bset
		mesh->DrawSubset(i);
	}

	effect->EndPass();
	effect->End();
}
//開放。
void Player::Release()
{
	// マテリアルバッファを解放。
	if (pD3DXMtrlBuffer != NULL){
		pD3DXMtrlBuffer->Release();
		pD3DXMtrlBuffer = NULL;
	}
	
	//メッシュを開放。
	if (mesh != NULL) {
		mesh->Release();
		mesh = NULL;
	}
	//テクスチャを開放。
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
	//エフェクトを開放。
	if (effect != NULL) {
		effect->Release();
		effect = NULL;
	}
}