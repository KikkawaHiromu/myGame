#include"Player.h"

Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	m_img = COPY_RESOURCE("Player", CImage);
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
	
	const float move_speed = 4;
	bool move_flag = false;

	if (HOLD(CInput::eLeft)) {
		m_pos.x += -move_speed;
		m_flip = true;
		move_flag = true;
	}
	if (HOLD(CInput::eRight)) {
		m_pos.x += move_speed;
		m_flip = false;
		move_flag = true;
	}
	if (HOLD(CInput::eUp)) {
		m_pos.y -= move_speed;
		move_flag = true;
	}
	if (HOLD(CInput::eDown)) {
		m_pos.y += move_speed;
		move_flag = true;
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
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}

void Player::Collision(Base* b)
{
}