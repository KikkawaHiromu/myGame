#pragma once
#include"../Base/Base.h"

class Girl :public Base {
private:
	int m_state;
	bool m_flip;
	int m_damage_no;
	int hp;

	CImage m_img;

	void StateIdle();
	void StateWait();
	void StateFound();
	void StateCry();
	void StateDamage();
	void StateDown();
public:
	enum {
		eState_Idle,
		eState_Wait,
		eState_Found,
		eState_Cry,
		eState_Damage,
		eState_Down,
	};
	Girl(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
};