#pragma once
#include"../Base/Base.h"
class Player :public Base {
private:
	enum {
		eState_Idle,
		eState_Attack,
		eState_Down,
	};
	int m_state;
	bool m_flip;
	int m_attack_no;
	int m_damage_no;

	CImage m_img;

	void StateIdle();
	void StateAttack();
	void StateDown();

public:
	Player(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
};