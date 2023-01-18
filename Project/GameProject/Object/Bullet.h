#pragma once
#include"../Base/Base.h"
class Bullet :public Base {
public:
	CImage m_img;
	bool m_flip;
	int m_attack_no;
	int m_cnt;

public:
	Bullet(const CVector2D& pos, float ang, int attack_no);
	void Update();
	void Draw();
	int GetAttackNo() {
		return m_attack_no;
	}
	void Collision(Base* b);
};