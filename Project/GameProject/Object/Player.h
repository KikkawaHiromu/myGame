#pragma once
#include"../Base/Base.h"
extern TexAnimData player_anim_data[];

class Player :public Base {
private:
	enum{
		eState_Idle��,eState_Attack��,eState_Down��,
		eState_Idle��,eState_Attack��,eState_Down��,
		eState_Idle��,eState_Attack��,eState_Down��,
	};
	enum {
		eAnimIdle��,
		eAnimHide��,
		eAnimAttack��,
		eAnimDown��,
		eAnimIdle��,
		eAnimHide��,
		eAnimAttack��,
		eAnimDown��,
		eAnimIdle��,
		eAnimHide��,
		eAnimAttack��,
		eAnimDown��,
	};
	int m_state;
	int m_attack_no;
	int m_damage_no;
	int m_cnt;
	bool m_flip;

	CImage m_img;
	void StateIdle��();
	void StateAttack��();
	void StateDown��();
	void StateIdle��();
	void StateAttack��();
	void StateDown��();
	void StateIdle��();
	void StateAttack��();
	void StateDown��();

	CVector2D m_move_speed;
public:
	Player(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
};