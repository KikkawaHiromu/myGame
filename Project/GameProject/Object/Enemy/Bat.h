#pragma once
#include"../../Base/Base.h"
extern TexAnimData bat_anim_data[];

class Bat :public Base {
private:
	enum {
		eState_Idle,
		eState_Attack,
		eState_Wait,
		eState_Damage,
		eState_Down,
	};
	enum {
		eAnimIdle,
		eAnimAttack,
		eAnimDamage,
		eAnimDown,
	};
	void StateIdle();
	void StateAttack();
	void StateWait();
	void StateDamage();
	void StateDown();

	int m_state;

	bool m_flip;
	int hp;
	int m_cnt;
	int m_downC;
	int m_attack_no;
	int m_damage_no;
	bool m_is_sky;
	CImage m_img;
public:
	Bat(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}
};
