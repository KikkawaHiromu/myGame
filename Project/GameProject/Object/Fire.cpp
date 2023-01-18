#include "Fire.h"
#include"Player.h"
#include"../Game/Field.h"

static TexAnim fire[] = {
	{ 0,8 },
	{ 1,8 },
	{ 2,8 },
};
TexAnimData fire_anim_data[] = {
	ANIMDATA(fire),
};
Fire::Fire(const CVector2D& pos,bool flip, int attack_no) : Base(eType_Fire) {
	m_img = COPY_RESOURCE("Fire", CImage);
	m_pos = pos;
	m_img.SetSize(170, 170);
	m_img.SetCenter(85, 85);
	m_rect = CRect(-85, -85, 85, 85);
	m_img.ChangeAnimation(eAnimFire);
	m_attack_no = attack_no;
	m_cnt = 30;
}
void Fire::Update() {
	m_img.UpdateAnimation();
	CVector2D firePos = m_pos;
	CVector2D mousePos = CInput::GetMousePoint();
	CVector2D vec = mousePos - m_pos;
	CVector2D v = mousePos - m_pos;
	m_ang = atan2(vec.x, vec.y); distance = pow(mousePos.x - m_pos.x, 2) + pow(mousePos.y - m_pos.y, 2);
	have_distance = distance >= 1000;

	Base* player = Base::FindObject(eType_Player);
	if (player) {
		const float speed = 16;
		if (HOLD(CInput::eMouseL) && have_distance) {
			if (distance >= 300000) {
				m_pos += v.GetNormalize() * speed * 2;
			}
			m_pos += v.GetNormalize() * speed;
		}
		/*CVector2D vec = player->m_pos - m_pos;
		if (vec.Length() > 0) {
			m_ang = atan2(vec.x, vec.y);
			CVector2D dir(sin(m_ang), cos(m_ang));	
			m_pos += dir * speed;
		}*/
	}

	if (--m_cnt <= 0) {
		SetKill();
	}
}
void Fire::Draw() {
	m_img.SetPos(m_pos);
	m_img.SetAng(m_ang);
	m_img.Draw();
}
void Fire::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Field:
		if (Field* f = dynamic_cast<Field*>(b)) {
			if (m_pos.y > f->GetGroundY() - 85) {
				m_pos.y = f->GetGroundY() - 85;
			}
		}
		break;
	}
}