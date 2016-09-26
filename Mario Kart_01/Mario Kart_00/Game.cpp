/*!
* @brief	ゲーム
*/
#include "stdafx.h"
#include "Camera.h"
#include "game.h"
#include "Course.h"
#include "SkyBox.h"
#include "text.h"

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
SkyBox skybox;
Text text;


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
	skybox.Init(g_pd3dDevice);
	//カメラの初期化。
	gameCamera.Start(&player);	
	text.Init();
	player.course = &course;
}
/*! 
* @brief	更新。
*/
void Game::Update()
{
	gameCamera.PreUpdate();
	player.Update();
	gameCamera.Update();
	course.Update();
	skybox.Update();
	pat.Update();
}
/*!
* @brief	描画。
*/
void Game::Render()
{
	// 画面をクリア。
	
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
	skybox.Render(
		g_pd3dDevice,
		GetCamera().GetViewMatrix(),
		GetCamera().GetProjectionMatrix(),
		g_diffuseLightDirection,
		g_diffuseLightColor,
		g_ambientLight,
		LIGHT_NUM
		);
	text.Render();
}
void Game::Terminate()
{
	player.Release();
	course.Release();
	skybox.Release();
}
