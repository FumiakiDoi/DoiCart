//�R���g���[���[

#pragma once

#include <XInput.h>

	class CPad{
	public:
		CPad();
		~CPad();
		struct PAD_STATE
		{
			XINPUT_STATE state;
			bool bConnected;
		};
		void Init(int padNo)
		{
			m_padNo = padNo;
		}
		//�X�V
		void Update();
		/*@brief	�{�^���̃g���K�[����B
			*@return	true���Ԃ��Ă�����g���K�[���́B
			*/
		bool IsTrigger(EnButton button) const
		{
			//TK_ASSERT(button < enButtonNum, "button is invalid");
			return m_trigger[button] != 0;
		}
		/*!
		*@brief	�{�^����������Ă��邩����B
		*@return	true���Ԃ��Ă����牟����Ă���B
		*/
		bool IsPress(EnButton button) const
		{
			//TK_ASSERT(button < enButtonNum, "button is invalid");
			return m_press[button] != 0;
		}
		//���X�e�B�b�N��X���̓��͗ʂ��擾�B
		//return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
		float GetLStickXF() const
		{
			return m_lStickX;
		}
		//brief	���X�e�B�b�N��Y���̓��͗ʂ��擾�B
		//return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
		float GetLStickYF() const
		{
			return m_lStickY;
		}
		//�E�X�e�B�b�N��X���̓��͗ʂ��擾�B
		//return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
		float GetRStickXF() const
		{
			return m_rStickX;
		}
		//�E�X�e�B�b�N��Y���̓��͗ʂ��擾�B
		//return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
		float GetRStickYF() const
		{
			return m_rStickY;
		}
	private:
		PAD_STATE m_state;	//!<�p�b�h�X�e�[�g�B
		int m_padNo;		//!<�p�b�h�ԍ��B
		int m_trigger[enButtonNum];	//!<�g���K�[���͂̃t���O�B
		int m_press[enButtonNum];	//!<press���͂̃t���O�B
		float m_lStickX;			//!<���X�e�B�b�N��X���̓��͗ʁB
		float m_lStickY;			//!<���X�e�B�b�N��Y���̓��͗ʁB
		float m_rStickX;			//!<�E�X�e�B�b�N��X���̓��͗ʁB
		float m_rStickY;			//!<�E�X�e�B�b�N��Y���̓��͗ʁB
#define		r_cast		reinterpret_cast
#define		s_cast		static_cast
#define		c_cast		const_cast
	};

