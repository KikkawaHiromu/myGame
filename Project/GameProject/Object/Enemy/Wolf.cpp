#include"Wolf.h"
#include"../../Game/Field.h"
#include"../Bullet.h"
#include"../Fire.h"

static TexAnim WolfIdle[] = {
	{ 0,40 },
	{ 1,40 },
};
static TexAnim WolfWait[] = {
	{ 3,100 },
	{ 3,1 },
};
static TexAnim WolfAttack[] = {
	{ 2,40 }
};
static TexAnim WolfDamage[] = {
	{ 0,4 },
	{ 4,4 },
	{ 0,4 },
	{ 4,4 },
	{ 0,4 },
	{ 4,4 },
};
static TexAnim WolfDown[] = {
	{ 0,4 },
	{ 4,4 },
	{ 0,4 },
	{ 4,4 },
	{ 0,4 },
	{ 4,4 },
	{ 0,4 },
};
TexAnimData wolf_anim_data[] = {
	ANIMDATA(WolfIdle), 
	ANIMDATA(WolfWait),
	ANIMDATA(WolfAttack),
	ANIMDATA(WolfDamage),
	ANIMDATA(WolfDown),
};
Wolf::Wolf(const CVector2D& p, bool flip) :Base(eType_Wolf) {
	m_img = COPY_RESOURCE("Wolf", CImage);
	m_img.SetSize(250, 147);
	m_img.SetCenter(125, 73);
	m_pos = p;
	m_flip = flip;
	m_rect = CRect(-125, -73, 125, 73);
	m_state = eState_Idle;
	m_attack_no = rand();
	m_damage_no = -1;
	m_is_ground;
	hp = 90;
	m_cnt = 0;
	m_DownC = 80;
}

void Wolf::StateIdle() {
	//m_rect = CRect(-100, -35, 100, 70);
	m_img.ChangeAnimation(eAnimIdle);
	const float move_speed = 5;
	bool move_flag = false;
	Base* girl = Base::FindObject(eType_Girl);

	if (girl) {
		if (girl->m_pos.x > m_pos.x + 125) {
			m_pos.x += move_speed;
			m_flip = true;
			move_flag = true;
		}
		else
			if (girl->m_pos.x < m_pos.x - 125) {
				m_pos.x += -move_speed;
				m_flip = false;
				move_flag = true;
			}
			else {
				m_cnt += 10;
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
void Wolf::StateAttack() {
	m_img.ChangeAnimation(eAnimAttack);
	if (m_flip) {
		m_pos.x -= 5;
	}
	else {
		m_pos.x += 5;
	}
	if (--m_cnt <= 0) {
		m_state = eState_Idle;
	}
}
void Wolf::StateDamage() {
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Wolf::StateDown() {
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
		if (--m_DownC <= 0) {
			m_kill = true;
		}
	}
}

void Wolf::Update() {
	switch (m_state) {
	case eState_Idle:
		StateIdle();
		break;
	case eState_Attack:
		StateAttack();
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
void Wolf::Draw() {
	m_img.SetPos(m_pos);
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}
void Wolf::Collision(Base* b) {
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