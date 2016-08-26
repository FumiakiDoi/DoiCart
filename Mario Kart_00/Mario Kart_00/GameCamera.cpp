#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"


GameCamera::GameCamera() :
toEyePos(0.0f, 0.0f, 0.0f, 1.0f),
targetOffset(0.0f, 0.0f, 0.0f, 1.0f),
cameraDir(0.0f, 0.0f, 0.0f),
state(cameraback)

{
	frg = false;
}
GameCamera::~GameCamera()
{
}
void GameCamera::Start(Player* player)
{
	toEyePos.x = -0.0f;
	toEyePos.y = 1.5f;
	toEyePos.z = -4.0f;		//カメラ位置
	

	targetOffset.y = 0.0f;
	targetOffset.x = 0.0f;
	camera.SetAspect(1280.0f / 720.0f);
	camera.Init();
	this->player = player;
	UpdateCamera();
}
//カメラを更新。
void GameCamera::UpdateCamera()
{
	
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (frg == false)
		{
			if (state == cameraback){

				toEyePos.y = 0.5f;
				toEyePos.z = -5.0f;		//カメラ位置
			
				state = camerain;
			}
			else if (state == camerain){
				toEyePos.y = 2.0f;
				toEyePos.z = -10.0f;		//カメラ位置
				
				state = cameraflont;
			}
			else if (state == cameraflont){
				toEyePos.y = 0.5f;
				toEyePos.z = -4.0f;		//カメラ位置
				
				state = cameraback;
			}
		}
		frg = true;
	}
	else 
	{
		frg = false;
	}
	D3DXVECTOR3 target;

	target = player->GetPosition();
	target.x += targetOffset.x;
	target.y += targetOffset.y;
	target.z += targetOffset.z;
	D3DXVECTOR3 eyePos = target;
	eyePos.x += toEyePos.x;
	eyePos.y += toEyePos.y;
	eyePos.z += toEyePos.z;

	camera.SetEyePt(eyePos);
	camera.SetLookatPt(target);
	camera.Update();
}
void GameCamera::PreUpdate()
{
	cameraDir = D3DXVECTOR3(toEyePos);
	cameraDir.y = 0.0f;
	D3DXVec3Normalize(&cameraDir, &cameraDir);
}
void GameCamera::Update()
{
	UpdateCamera();
}