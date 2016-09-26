//コントローラー

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
		//更新
		void Update();
		/*@brief	ボタンのトリガー判定。
			*@return	trueが返ってきたらトリガー入力。
			*/
		bool IsTrigger(EnButton button) const
		{
			//TK_ASSERT(button < enButtonNum, "button is invalid");
			return m_trigger[button] != 0;
		}
		/*!
		*@brief	ボタンが押されているか判定。
		*@return	trueが返ってきたら押されている。
		*/
		bool IsPress(EnButton button) const
		{
			//TK_ASSERT(button < enButtonNum, "button is invalid");
			return m_press[button] != 0;
		}
		//左スティックのX軸の入力量を取得。
		//return	-1.0～1.0の正規化された値を返す。
		float GetLStickXF() const
		{
			return m_lStickX;
		}
		//brief	左スティックのY軸の入力量を取得。
		//return	-1.0～1.0の正規化された値を返す。
		float GetLStickYF() const
		{
			return m_lStickY;
		}
		//右スティックのX軸の入力量を取得。
		//return	-1.0～1.0の正規化された値を返す。
		float GetRStickXF() const
		{
			return m_rStickX;
		}
		//右スティックのY軸の入力量を取得。
		//return	-1.0～1.0の正規化された値を返す。
		float GetRStickYF() const
		{
			return m_rStickY;
		}
	private:
		PAD_STATE m_state;	//!<パッドステート。
		int m_padNo;		//!<パッド番号。
		int m_trigger[enButtonNum];	//!<トリガー入力のフラグ。
		int m_press[enButtonNum];	//!<press入力のフラグ。
		float m_lStickX;			//!<左スティックのX軸の入力量。
		float m_lStickY;			//!<左スティックのY軸の入力量。
		float m_rStickX;			//!<右スティックのX軸の入力量。
		float m_rStickY;			//!<右スティックのY軸の入力量。
#define		r_cast		reinterpret_cast
#define		s_cast		static_cast
#define		c_cast		const_cast
	};

