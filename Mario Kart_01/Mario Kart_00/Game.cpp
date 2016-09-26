/*!
* @brief	�Q�[��
*/
#include "stdafx.h"
#include "Camera.h"
#include "game.h"
#include "Course.h"
#include "SkyBox.h"
#include "text.h"

/*!
* @brief	�R���X�g���N�^�B
*/
Game::Game()
{
}
/*!
* @brief	�f�X�g���N�^�B
*/
Game::~Game()
{
	
}
const int				LIGHT_NUM = 4;
D3DXVECTOR4 			g_diffuseLightDirection[LIGHT_NUM];	//���C�g�̕����B
D3DXVECTOR4				g_diffuseLightColor[LIGHT_NUM];		//���C�g�̐F�B
D3DXVECTOR4				g_ambientLight;						//����

Course course;
SkyBox skybox;
Text text;


/*!
* @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
*/
void UpdateLight()
{
	g_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	g_diffuseLightDirection[1] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	g_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 1.0f);
	g_diffuseLightDirection[3] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);

	//�f�B�t���[�Y���C�g�B
	g_diffuseLightColor[0] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	g_diffuseLightColor[1] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	g_diffuseLightColor[2] = D3DXVECTOR4(0.5f, 0.4f, 0.6f, 1.0f);
	g_diffuseLightColor[3] = D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f);

	//�����B
	g_ambientLight = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}
void Game::Start()
{
	//���C�g���������B
	ZeroMemory(g_diffuseLightDirection, sizeof(g_diffuseLightDirection));
	ZeroMemory(g_diffuseLightColor, sizeof(g_diffuseLightColor));
	player.Init(g_pd3dDevice);
	course.Init(g_pd3dDevice);
	skybox.Init(g_pd3dDevice);
	//�J�����̏������B
	gameCamera.Start(&player);	
	text.Init();
	player.course = &course;
}
/*! 
* @brief	�X�V�B
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
* @brief	�`��B
*/
void Game::Render()
{
	// ��ʂ��N���A�B
	
	//Player��`��B
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
