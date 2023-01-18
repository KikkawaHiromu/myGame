#include "Bullet.h"
#include "Player.h"

Bullet::Bullet(const CVector2D& pos, float ang, int attack_no) :Base(eType_Bullet) {
	m_img = COPY_RESOURCE("Bullet", CImage);
	m_pos = pos;
	m_rad = 25;
	m_ang = ang;
	m_img.SetSize(90, 90);
	m_img.SetCenter(45, 45);
	m_attack_no = attack_no;
	m_cnt = 80;
}

void Bullet::Update()
{
	static const float move_speed = 15;
	m_pos.x += sinf(m_ang) * move_speed;
	m_pos.y += cosf(m_ang) * move_speed;
	
	if (--m_cnt <= 0) {
		m_kill = true;
	}
}

void Bullet::Draw()
{
	m_img.SetPos(m_pos);
	m_img.SetAng(m_ang);
	m_img.Draw();

}

void Bullet::Collision(Base* b)
{

}
