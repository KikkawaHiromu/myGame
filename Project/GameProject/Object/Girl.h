#pragma once
#include"../Base/Base.h"
extern TexAnimData girl_anim_data[];

class Girl :public Base {
private:
	enum {
		eAnimIdle,
		eAnimWait,
		eAnimDamage,
		eAnimDown,
	};
	int m_state;
	bool m_flip;
	int m_damage_no;
	int hp;
	int m_cnt;
	bool m_is_ground;

	CImage m_img;

	void StateIdle();
	void StateWait();
	void StateDamage();
	void StateDown();
public:
	enum {
		eState_Idle,
		eState_Wait,
		eState_Damage,
		eState_Down,
	};
	Girl(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);

};