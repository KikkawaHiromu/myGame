#pragma once
#include"../Base/Base.h"
extern TexAnimData player_anim_data[];

class Player :public Base {
private:
	enum{
		eState_IdleÔ,eState_AttackÔ,eState_DownÔ,
		eState_IdleÂ,eState_AttackÂ,eState_DownÂ,
		eState_Idle‡,eState_Attack‡,eState_Down‡,
	};
	enum {
		eAnimIdleÔ,
		eAnimHideÔ,
		eAnimAttackÔ,
		eAnimDownÔ,
		eAnimIdleÂ,
		eAnimHideÂ,
		eAnimAttackÂ,
		eAnimDownÂ,
		eAnimIdle‡,
		eAnimHide‡,
		eAnimAttack‡,
		eAnimDown‡,
	};
	int m_state;
	int m_attack_no;
	int m_damage_no;
	int m_cnt;
	bool m_flip;

	CImage m_img;
	void StateIdleÔ();
	void StateAttackÔ();
	void StateDownÔ();
	void StateIdleÂ();
	void StateAttackÂ();
	void StateDownÂ();
	void StateIdle‡();
	void StateAttack‡();
	void StateDown‡();

	CVector2D m_move_speed;
public:
	Player(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
};