#include"Bat.h"
#include"../../Game/Field.h"
#include"../Bullet.h"
#include"../Fire.h"

static TexAnim BatIdle[] = {
	{ 1,15 },
	{ 0,15 },
};
static TexAnim BatAttack[] = {
	{ 1,1 },
	{ 1,1 },
};
static TexAnim BatDamage[] = {
	{ 1,4 },
	{ 2,4 },
	{ 1,4 },
	{ 2,4 },
	{ 1,4 },
	{ 2,4 },
};
static TexAnim BatDown[] = {
	{ 1,4 },
	{ 2,4 },
	{ 1,4 },
	{ 2,4 },
	{ 1,4 },
	{ 2,4 },
	{ 1,4 },
};
TexAnimData bat_anim_data[] = {
	ANIMDATA(BatIdle),
	ANIMDATA(BatAttack),
	ANIMDATA(BatDamage),
	ANIMDATA(BatDown),
};
Bat::Bat(const CVector2D& p, bool flip) :Base(eType_Bat) {
	m_img = COPY_RESOURCE("Bat", CImage);
	m_img.SetSize(140,130 );
	m_img.SetCenter(70, 65);
	m_pos = p;
	m_flip = flip;
	m_rect = CRect(-70, -65, 75, 65);
	m_state = eState_Idle;
	m_attack_no = rand();
	m_damage_no = -1;
	m_is_sky;
	hp = 90;
	m_cnt = 0;
	m_downC = 80;
}

void Bat::StateIdle() {
	m_img.ChangeAnimation(eAnimIdle);
	const float move_speed = 3;
	bool move_flag = true;
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
void Bat::StateAttack() {
	const float move_speed = 6;
	if (m_flip) {
		m_pos.x += move_speed;
	}
	else {
		m_pos.x += -move_speed;
	}
	const float fall_pow = 16;
	if (m_is_sky) {
		m_vec.y = fall_pow;
		m_is_sky = false;
	}
	if (!m_is_sky) {
		if (m_vec.y < 0){
			m_img.ChangeAnimation(eAnimAttack, false);
			if (m_img.CheckAnimationEnd()) {
				m_cnt += 200;
				m_state = eState_Wait;
			}
		}
	}
}
void Bat::StateWait() {
	m_img.ChangeAnimation(eAnimIdle);
	const float move_speed = 3;
	bool move_flag = true;
	if (m_flip) {
		m_pos.x += move_speed;
	}
	else {
		m_pos.x -= move_speed;
	}

	if (--m_cnt <= 0) {
		m_state = eState_Idle;
	}
}
void Bat::StateDamage() {
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Bat::StateDown() {
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

void Bat::Update() {
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

	if (m_is_sky && m_vec.y > GRAVITY * 4)
		m_is_sky = false;
	m_vec.y -= GRAVITY;
	m_pos += m_vec;
}
void Bat::Draw() {
	m_img.SetPos(m_pos);
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}
void Bat::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Field:
		if (Field* f = dynamic_cast<Field*>(b)) {
			if (m_pos.y < f->GetSkyY() + 300) {
				m_pos.y = f->GetSkyY() + 300;
				m_vec.y = 0;
				m_is_sky = true;
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