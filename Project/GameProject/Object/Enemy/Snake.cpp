#include"Snake.h"
#include"../../Game/Field.h"
#include"../Bullet.h"
#include"../Fire.h"

static TexAnim SnakeIdle[] = {
	{ 1,20 },
	{ 0,20 },
};
static TexAnim SnakeJumpUp[] = {
	{ 2,5 },
};
static TexAnim SnakeJumpDown[] = {
	{ 3,20 },
};
static TexAnim SnakeDamage[] = {
	{ 1,4 },
	{ 4,4 },
	{ 1,4 },
	{ 4,4 },
	{ 1,4 },
	{ 4,4 },
};
static TexAnim SnakeDown[] = {
	{ 0,4 },
	{ 4,4 },
	{ 0,4 },
	{ 4,4 },
	{ 0,4 },
	{ 4,4 },
	{ 0,4 },
};
TexAnimData snake_anim_data[] = {
	ANIMDATA(SnakeIdle),
	ANIMDATA(SnakeJumpUp),
	ANIMDATA(SnakeJumpDown),
	ANIMDATA(SnakeDamage),
	ANIMDATA(SnakeDown),
};
Snake::Snake(const CVector2D& p, bool flip) :Base(eType_Snake) {
	m_img = COPY_RESOURCE("Snake", CImage);
	m_img.SetSize(200, 140);
	m_img.SetCenter(100, 70);
	m_pos = p;
	m_flip = flip;
	m_rect = CRect(-80, -35, 80, 70);
	m_state = eState_Idle;
	m_attack_no = rand();
	m_damage_no = -1;
	m_is_ground;
	hp = 90;
	m_cnt = 0;
	m_downC = 80;
}

void Snake::StateIdle() {
	//m_rect = CRect(-100, -35, 100, 70);
	m_img.ChangeAnimation(eAnimIdle);
	const float move_speed = 3;
	bool move_flag = false;
	Base* girl = Base::FindObject(eType_Girl);

	if (girl) {
		if (girl->m_pos.x > m_pos.x + 150) {
			m_pos.x += move_speed;
			m_flip = true;
			move_flag = true;
		}
		else
			if (girl->m_pos.x < m_pos.x - 150) {
				m_pos.x += -move_speed;
				m_flip = false;
				move_flag = true;
			}
			else {
				m_state = eState_Attack;
				m_attack_no++;
			}
		if (move_flag) {
			m_img.ChangeAnimation(eAnimIdle);
		}
		else {
			m_img.ChangeAnimation(eAnimIdle);
		}
	}
}
void Snake::StateAttack() {
	const float move_speed = 7;
	if (m_flip) {
		m_pos.x += move_speed;
	}
	else {
		m_pos.x += -move_speed;
	}
	const float jump_pow = 12;
	if (m_is_ground) {
	 m_vec.y = -jump_pow;
	 m_is_ground = false;
	}
	if (!m_is_ground) {
		if (m_vec.y < 0)
			m_img.ChangeAnimation(eAnimJumpUp, false);
		else {
			m_img.ChangeAnimation(eAnimJumpDown, false);
			if (m_img.CheckAnimationEnd()) {
				m_cnt += 30;
				m_state = eState_Wait;
			}
		}
	}
}
void Snake::StateWait() {
	m_img.ChangeAnimation(eAnimIdle);
	if (--m_cnt <= 0) {
		m_state = eState_Idle;
	}
}
void Snake::StateDamage() {
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Snake::StateDown() {
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		Base* girl = Base::FindObject(eType_Girl);
		if (girl) {
			if (girl->m_pos.x > m_pos.x + 150) {
				m_flip = false;
			}
			else
				if (girl->m_pos.x < m_pos.x - 150) {
					m_flip = true;
				}
			const float move_speed = 15;
			if (m_flip) {
				m_pos.x += move_speed;
			}
			else {
				m_pos.x += -move_speed;
			}
		}
		if (--m_downC <= 0) {
			m_kill = true;
		}
	}
}

void Snake::Update() {
	switch (m_state) {
	case eState_Idle:
		StateIdle();
		break;
	case eState_Attack:
		StateAttack();
		break;
	case eState_Wait:
		StateWait();
		break;
	case eState_Damage:
		StateDamage();
		break;
	case eState_Down:
		StateDown();
		break;
	}
	m_img.UpdateAnimation();

	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	m_vec.y += GRAVITY;
	m_pos += m_vec;
}
void Snake::Draw() {
	m_img.SetPos(m_pos);
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}
void Snake::Collision(Base*b) {
	switch (b->m_type) {
	case eType_Field:
		if (Field* f = dynamic_cast<Field*>(b)) {
			if (m_pos.y > f->GetGroundY() - 60) {
				m_pos.y = f->GetGroundY() - 60;
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;
	case eType_Fire:
		if (Fire* f = dynamic_cast<Fire*>(b)) {
			if (Base::CollisionRect(this, f)) {
				if (m_damage_no != f->GetAttackNo() && Base::CollisionRect(this, f)) {
					//“¯‚¶UŒ‚‚Ì˜A‘±ƒ_ƒ[ƒW–hŽ~
					m_damage_no = f->GetAttackNo();
					hp -= 90;
					if (hp <= 0) {
						m_state = eState_Down;
					}
					else {
						m_state = eState_Damage;
					}
				}
			}
		}
		break;
	case eType_Bullet:
		if (Bullet* n = dynamic_cast<Bullet*>(b)) {
			if (Base::CollisionRect(this, n)) {
				n->SetKill();
				hp -= 30;
				if (hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
			}
		}
		break;
	}
}