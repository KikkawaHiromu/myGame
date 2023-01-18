#pragma once
#include"../../Base/Base.h"
extern TexAnimData wolf_anim_data[];

class Wolf :public Base {
private:
	enum {
		eState_Idle,
		eState_Attack,
		eState_Damage,
		eState_Down,
	};
	enum {
		eAnimIdle,
		eAnimWait,
		eAnimAttack,
		eAnimDamage,
		eAnimDown,
	};
	void StateIdle();
	void StateAttack();
	void StateDamage();
	void StateDown();

	int m_state;
	bool m_flip;
	int hp;
	int m_cnt;
	int m_DownC;
	int m_attack_no;
	int m_damage_no;
	bool m_is_ground;
	CImage m_img;
public:
	Wolf(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}
};