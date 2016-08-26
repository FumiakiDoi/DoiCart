/*!
* @brief	�Q�[���N���X�B
*/

#pragma once

#include "Player.h"
#include "GameCamera.h"




/*!
* @brief	�Q�[���N���X�B
*/
class Game{
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	Game();
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~Game();
	/*!
	* @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
	*/
	void Start();
	/*!
	* @brief	�X�V�B
	*/
	void Update();
	/*!
	* @brief	�`��B
	*/
	void Render();
	/*!
	* @brief	�J�������擾�B
	*/
	void UpdateLight();
	void Terminate();
	const Camera& GetCamera() const
	{
		return gameCamera.GetCamera();
	}
	/*!
	* @brief	�Q�[���J�������擾�B
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
	GameCamera gameCamera;			//�Q�[���J�����B
	Player player;					//�v���C���[�B
};

extern Game* game;