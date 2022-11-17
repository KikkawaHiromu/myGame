#include"Player.h"

Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	m_img = COPY_RESOURCE("Player_’Êí", CImage);
	m_pos = p;
	m_img.SetCenter(50,50);
	m_img.SetSize(100, 100);
	m_rect = CRect(-10, -10, 10, 10);
	m_flip = flip;
	m_state = eState_Idle;
	m_attack_no = rand();
	m_damage_no = -1;
}

void Player::StateIdle() {
	
	const float move_speed = 16;
	bool move_flag = false;
	/*
	if (HOLD(CInput::eButton2)) {
		m_pos.x += -move_speed;
		m_flip = true;
		move_flag = true;
	}
	if (HOLD(CInput::eButton3)) {
		m_pos.x += move_speed;
		m_flip = false;
		move_flag = true;
	}
	if (HOLD(CInput::eButton1)) {
		m_pos.y -= move_speed;
		move_flag = true;
	}
	if (HOLD(CInput::eButton4)) {
		m_pos.y += move_speed;
		move_flag = true;
	}
	*/
	CVector2D mousePos = CInput::GetMousePoint();
	CVector2D vec = mousePos - m_pos;
	CVector2D v = mousePos - m_pos;
	m_ang = atan2(vec.x, vec.y);
	distance = pow(mousePos.x - m_pos.x, 2) + pow(mousePos.y - m_pos.y, 2);
	have_distance = distance >= 1000;
	if (HOLD(CInput::eMouseL)&&have_distance) {
		if (distance >= 300000) {
			m_pos += v.GetNormalize() * move_speed * 2;
		}
		m_pos += v.GetNormalize() * move_speed;
	}
}
void Player::StateAttack() {

}
void Player::StateDown() {

}

void Player::Update() {
	switch (m_state) {
	case eState_Idle:
		StateIdle();
		break;
	case eState_Attack:
		StateAttack();
		break;
	case eState_Down:
		StateDown();
		break;
	}
}

void Player::Draw() {
	m_img.SetPos(m_pos);
	m_img.SetFlipH(m_flip);
	m_img.SetAng(m_ang);
	m_img.Draw();
}

void Player::Collision(Base* b)
{
}