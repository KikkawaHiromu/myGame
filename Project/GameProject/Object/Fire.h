#pragma once
#include "../Base/Base.h"
extern TexAnimData fire_anim_data[];

class Fire : public Base {
private:
	enum {
		eAnimFire,
	};
	CImage m_img;
	int m_cnt;
	bool m_flip;
	int m_attack_no;

public:
	Fire(const CVector2D& pos,bool flip,int attack_no);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}
};