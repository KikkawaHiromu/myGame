#include"Player.h"
#include"../Game/Field.h"
#include"Fire.h"
#include"Bullet.h"
#include"Enemy/Bat.h"
#include"Enemy/Snake.h"
#include"Enemy/Wolf.h"

static TexAnim playerIdleÔ[] = {
	{ 0,7 },
	{ 1,7 },
	{ 2,7 },
};
static TexAnim playerHideÔ[] = {
	{ 3,7 },
	{ 4,7 },
	{ 5,7 },
};
static TexAnim playerAttackÔ[] = {
	{ 0,1 },
};
static TexAnim playerDownÔ[] = {
	{ 0,5 },
	{ 6,5 },
	{ 0,5 },
	{ 6,5 },
	{ 0,5 },
	{ 6,5 },
	{ 0,5 },
	{ 6,5 },
};
static TexAnim playerIdleÂ[] = {
	{ 7,7 },
	{ 8,7 },
	{ 9,7 },
};
static TexAnim playerHideÂ[] = {
	{ 10,7 },
	{ 11,7 },
	{ 12,7 },
};
static TexAnim playerAttackÂ[] = {
	{ 0,1 },
};
static TexAnim playerDownÂ[] = {
	{ 7,5 },
	{ 6,5 },
	{ 7,5 },
	{ 6,5 },
	{ 7,5 },
	{ 6,5 },
	{ 7,5 },
	{ 6,5 },
};
static TexAnim playerIdle‡[] = {
	{ 14,7 },
	{ 15,7 },
	{ 16,7 },
};
static TexAnim playerHide‡[] = {
	{ 17,7 },
	{ 18,7 },
	{ 19,7 },
};
static TexAnim playerAttack‡[] = {
	{ 0,1 },
};
static TexAnim playerDown‡[] = {
	{ 14,5 },
	{ 6,5 },
	{ 14,5 },
	{ 6,5 },
	{ 14,5 },
	{ 6,5 },
	{ 14,5 },
	{ 6,5 },
};
TexAnimData player_anim_data[] = {
	ANIMDATA(playerIdleÔ),
	ANIMDATA(playerHideÔ),
	ANIMDATA(playerAttackÔ),
	ANIMDATA(playerDownÔ),
	ANIMDATA(playerIdleÂ),
	ANIMDATA(playerHideÂ),
	ANIMDATA(playerAttackÂ),
	ANIMDATA(playerDownÂ),
	ANIMDATA(playerIdle‡),
	ANIMDATA(playerHide‡),
	ANIMDATA(playerAttack‡),
	ANIMDATA(playerDown‡),
};

Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	m_pos = p;
	m_rect = CRect(-30, -30, 30, 30);
	m_cnt;
	m_flip = flip;
	m_state = eState_IdleÔ;
	m_attack_no = rand();
	m_damage_no = -1;
	m_img = COPY_RESOURCE("Player", CImage);
	m_img.SetCenter(75, 75);
	m_img.SetSize(150, 150);
}

void Player::StateIdleÔ() {
	if (HOLD(CInput::eButton5)) {
		m_img.ChangeAnimation(eAnimHideÔ);
	}else{ 
		m_img.ChangeAnimation(eAnimIdleÔ); 
	}
	const float move_speed = 16;
	bool move_flag = false;
	
	CVector2D playerPos = m_pos;
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
	if (PUSH(CInput::eButton3)) {
		m_state = eState_IdleÂ;
	}
	if (PUSH(CInput::eButton4)) {
		m_state = eState_Idle‡;
	}
	if (PUSH(CInput::eButton1)) {
		m_state=eState_AttackÔ;
	}

}
void Player::StateAttackÔ() {
	Base::Add(new Fire(m_pos + CVector2D(0, 0), m_flip, m_attack_no++));
	m_state = eState_IdleÔ;
}
void Player::StateDownÔ() {
	m_img.ChangeAnimation(eAnimDownÔ, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_IdleÔ;
	}
}

void Player::StateIdleÂ() {
	if (HOLD(CInput::eButton5)) {
		m_img.ChangeAnimation(eAnimHideÂ);
	}
	else {
		m_img.ChangeAnimation(eAnimIdleÂ);
	}
	const float move_speed = 8;
	bool move_flag = false;
	
	CVector2D mousePos = CInput::GetMousePoint();
	CVector2D vec = mousePos - m_pos;
	CVector2D v = mousePos - m_pos;
	m_ang = atan2(vec.x, vec.y);
	distance = pow(mousePos.x - m_pos.x, 2) + pow(mousePos.y - m_pos.y, 2);
	have_distance = distance >= 1000;
	if (HOLD(CInput::eMouseL) && have_distance) {
		if (distance >= 300000) {
			m_pos += v.GetNormalize() * move_speed * 2;
		}
		m_pos += v.GetNormalize() * move_speed;
	}
	if (PUSH(CInput::eButton2)) {
		m_state = eState_IdleÔ;
	}
	if (PUSH(CInput::eButton4)) {
		m_state = eState_Idle‡;
	}
	if (PUSH(CInput::eButton1)) {
		m_state = eState_AttackÂ;
	}
}
void Player::StateAttackÂ() {
	Base::Add(new Bullet(m_pos + CVector2D(0, 0), m_ang, m_attack_no++));
	m_state = eState_IdleÂ;
}
void Player::StateDownÂ() {
	m_img.ChangeAnimation(eAnimDownÂ, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_IdleÂ;
	}
}
void Player::StateIdle‡() {
	if (HOLD(CInput::eButton5)) {
		m_img.ChangeAnimation(eAnimHide‡);
	}
	else {
		m_img.ChangeAnimation(eAnimIdle‡);
	}
	const float move_speed = 12;
	bool move_flag = false;

	CVector2D mousePos = CInput::GetMousePoint();
	CVector2D vec = mousePos - m_pos;
	CVector2D v = mousePos - m_pos;
	m_ang = atan2(vec.x, vec.y);
	distance = pow(mousePos.x - m_pos.x, 2) + pow(mousePos.y - m_pos.y, 2);
	have_distance = distance >= 1000;
	if (HOLD(CInput::eMouseL) && have_distance) {
		if (distance >= 300000) {
			m_pos += v.GetNormalize() * move_speed * 2;
		}
		m_pos += v.GetNormalize() * move_speed;
	}
	if (PUSH(CInput::eButton2)) {
		m_state = eState_IdleÔ;
	}
	if (PUSH(CInput::eButton3)) {
		m_state = eState_IdleÂ;
	}
}
void Player::StateAttack‡() {

}
void Player::StateDown‡() {
	m_img.ChangeAnimation(eAnimDown‡, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle‡;
	}
}


void Player::Update() {
	switch (m_state) {
	case eState_IdleÔ:
		StateIdleÔ();
		break;
	case eState_AttackÔ:
		StateAttackÔ();
		break;
	case eState_DownÔ:
		StateDownÔ();
		break;
	case eState_IdleÂ:
		StateIdleÂ();
		break;
	case eState_AttackÂ:
		StateAttackÂ();
		break;
	case eState_DownÂ:
		StateDownÂ();
		break;
	case eState_Idle‡:
		StateIdle‡();
		break;
	case eState_Attack‡:
		StateAttack‡();
		break;
	case eState_Down‡:
		StateDown‡();
		break;
	}
	m_img.UpdateAnimation();
}

void Player::Draw() {
	m_img.SetPos(m_pos);
	m_img.SetAng(m_ang);
	m_img.Draw();
}

void Player::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Field:
		if (Field* f = dynamic_cast<Field*>(b)) {
			if (m_pos.y > f->GetGroundY() - 75) {
				m_pos.y = f->GetGroundY() - 75;
			}
		}
		break;
	case eType_Wolf:
		if (Wolf* w = dynamic_cast<Wolf*>(b)) {
			if (Base::CollisionRect(this, w)) {
				if (m_damage_no != w->GetAttackNo() && Base::CollisionRect(this, w)) {
					//“¯‚¶UŒ‚‚Ì˜A‘±ƒ_ƒ[ƒW–h~
					m_damage_no = w->GetAttackNo();
					switch (m_state) {
					case eState_IdleÔ:
						m_state = eState_DownÔ;
						break;
					case eState_IdleÂ:
						m_state = eState_DownÂ;
						break;
					case eState_Idle‡:
						m_state = eState_Down‡;
						break;
					}
				}
			}
		}
	case eType_Snake:
		if (Snake* s = dynamic_cast<Snake*>(b)) {
			if (Base::CollisionRect(this, s)) {
				if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
					//“¯‚¶UŒ‚‚Ì˜A‘±ƒ_ƒ[ƒW–h~
					m_damage_no = s->GetAttackNo();
					switch (m_state) {
					case eState_IdleÔ:
						m_state = eState_DownÔ;
						break;
					case eState_IdleÂ:
						m_state = eState_DownÂ;
						break;
					case eState_Idle‡:
						m_state = eState_Down‡;
						break;
					}
				}
			}
		}
	case eType_Bat:
		if (Bat* v = dynamic_cast<Bat*>(b)) {
			if (Base::CollisionRect(this, v)) {
				if (m_damage_no != v->GetAttackNo() && Base::CollisionRect(this, v)) {
					//“¯‚¶UŒ‚‚Ì˜A‘±ƒ_ƒ[ƒW–h~
					m_damage_no = v->GetAttackNo();
					switch (m_state) {
					case eState_IdleÔ:
						m_state = eState_DownÔ;
						break;
					case eState_IdleÂ:
						m_state = eState_DownÂ;
						break;
					case eState_Idle‡:
						m_state = eState_Down‡;
						break;
					}
				}
			}
		}
	}
}