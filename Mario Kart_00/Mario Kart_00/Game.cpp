/*!
* @brief	ゲーム
*/
#include "stdafx.h"
#include "Camera.h"
#include "game.h"
#include "Course.h"

/*!
* @brief	コンストラクタ。
*/
Game::Game()
{
}
/*!
* @brief	デストラクタ。
*/
Game::~Game()
{
	
}
const int				LIGHT_NUM = 4;
D3DXVECTOR4 			g_diffuseLightDirection[LIGHT_NUM];	//ライトの方向。
D3DXVECTOR4				g_diffuseLightColor[LIGHT_NUM];		//ライトの色。
D3DXVECTOR4				g_ambientLight;						//環境光


Course course;



/*!
* @brief	ゲームが起動してから一度だけ呼ばれる関数。
*/
void UpdateLight()
{
	g_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	g_diffuseLightDirection[1] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	g_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 1.0f);
	g_diffuseLightDirection[3] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);

	//ディフューズライト。
	g_diffuseLightColor[0] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	g_diffuseLightColor[1] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	g_diffuseLightColor[2] = D3DXVECTOR4(0.5f, 0.4f, 0.6f, 1.0f);
	g_diffuseLightColor[3] = D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f);

	//環境光。
	g_ambientLight = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}
void Game::Start()
{
	//ライトを初期化。
	ZeroMemory(g_diffuseLightDirection, sizeof(g_diffuseLightDirection));
	ZeroMemory(g_diffuseLightColor, sizeof(g_diffuseLightColor));
	player.Init(g_pd3dDevice);
	course.Init(g_pd3dDevice);
	player.SetPosition(D3DXVECTOR3(0, 0, 0));
	//カメラの初期化。
	gameCamera.Start(&player);	
}
/*! 
* @brief	更新。
*/
void Game::Update()
{
	gameCamera.PreUpdate();
	player.Update();
	gameCamera.Update();
}
/*!
* @brief	描画。
*/
void Game::Render()
{
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();
	//Playerを描画。
	player.Render(
		g_pd3dDevice,
		GetCamera().GetViewMatrix(),
		GetCamera().GetProjectionMatrix(),
		g_diffuseLightDirection,
		g_diffuseLightColor,
		g_ambientLight,
		LIGHT_NUM
		);
	course.Render(
		g_pd3dDevice,
		GetCamera().GetViewMatrix(),
		GetCamera().GetProjectionMatrix(),
		g_diffuseLightDirection,
		g_diffuseLightColor,
		g_ambientLight,
		LIGHT_NUM
		);
	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
void Game::Terminate()
{
	player.Release();
	course.Release();
}