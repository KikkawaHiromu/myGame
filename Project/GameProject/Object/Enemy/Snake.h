#pragma once
#include"../../Base/Base.h"
extern TexAnimData snake_anim_data[];

class Snake :public Base {
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
		eAnimJumpUp,
		eAnimJumpDown,
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
	bool m_is_ground;
	CImage m_img;
public:
	Snake(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}
};