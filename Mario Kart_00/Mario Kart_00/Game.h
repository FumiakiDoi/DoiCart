/*!
* @brief	ゲームクラス。
*/

#pragma once

#include "Player.h"
#include "GameCamera.h"




/*!
* @brief	ゲームクラス。
*/
class Game{
public:
	/*!
	* @brief	コンストラクタ。
	*/
	Game();
	/*!
	* @brief	デストラクタ。
	*/
	~Game();
	/*!
	* @brief	ゲームが起動してから一度だけ呼ばれる関数。
	*/
	void Start();
	/*!
	* @brief	更新。
	*/
	void Update();
	/*!
	* @brief	描画。
	*/
	void Render();
	/*!
	* @brief	カメラを取得。
	*/
	void UpdateLight();
	void Terminate();
	const Camera& GetCamera() const
	{
		return gameCamera.GetCamera();
	}
	/*!
	* @brief	ゲームカメラを取得。
	*/
	const GameCamera& GetGameCamera() const
	{
		return gameCamera;
	}
	
	Player* GetPlayer()
	{
		return &player;
	}
private:
	GameCamera gameCamera;			//ゲームカメラ。
	Player player;					//プレイヤー。
};

extern Game* game;