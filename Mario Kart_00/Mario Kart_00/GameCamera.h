#pragma once
#include "Camera.h"

class Player;

//ゲームカメラ
class GameCamera
{
public:
	GameCamera();
	~GameCamera();
	void Start(Player* player);
	void PreUpdate();
	void Update();
	//カメラを取得。
	const Camera& GetCamera() const
	{
		return camera;
	}
	//カメラの方向を取得。
	D3DXVECTOR3 GetCameraDir() const
	{
		return cameraDir;
	}

private:
	//カメラを更新。
	void UpdateCamera();
private:
	bool frg;
	Camera		camera;
	Player*		player;			//追従するプレイヤー。
	D3DXVECTOR4 targetOffset;	//注視点のオフセット。
	D3DXVECTOR4 toEyePos;		//注視点から視点までのベクトル。	
	D3DXVECTOR3 cameraDir;		//カメラの方向。
	enum State
	{
		cameraback,
		camerain,
		cameraflont
	};
	State state;		//今のカメラの状態。
	
};

