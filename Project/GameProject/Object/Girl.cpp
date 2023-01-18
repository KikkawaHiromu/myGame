#include"Girl.h"
#include"../Game/Field.h"
#include"Enemy/Bat.h"
#include"Enemy/Snake.h"
#include"Enemy/Wolf.h"

static TexAnim GirlIdle[] = {
	{ 0,30 },
	{ 1,30 },
	{ 2,30 },
	{ 1,30 },
};
static TexAnim GirlWait[] = {
	{ 2,20 },
};
static TexAnim GirlDamage[] = {
	{ 3,6 },
	{ 4,6 },
	{ 3,6 },
	{ 4,6 },
	{ 3,6 },
	{ 4,6 },
	{ 3,6 },
	{ 4,6 },
};
static TexAnim GirlDown[] = {
	{ 3,6 },
	{ 4,6 },
	{ 3,6 },
	{ 4,6 },
	{ 3,6 },
	{ 4,6 },
	{ 3,6 },
	{ 4,6 },
};
TexAnimData girl_anim_data[] = {
	ANIMDATA(GirlIdle),
	ANIMDATA(GirlWait),
	ANIMDATA(GirlDamage),
	ANIMDATA(GirlDown),
};

Girl::Girl(const CVector2D& p, bool flip):
	Base(eType_Girl){
	m_img = COPY_RESOURCE("Girl", CImage);
	m_pos = p;
	m_img.SetCenter(55,200);
	m_img.SetSize(110, 400);
	m_rect = CRect(-55, -200, 55, 0);
	m_flip = flip;
	m_is_ground;
	m_state = eState_Idle;
	m_damage_no = -1;
	m_cnt = 200;
	hp = 100;
}

void Girl::StateIdle() {
	m_img.ChangeAnimation(eAnimIdle);
	const float move_speed = 1.5;
	m_pos.x += move_speed;
	bool move_flag = true;
	m_flip = false;
	
	/*if (--m_cnt <= 0) {
		m_cnt = rand() % 120 + 180;
		m_state = eState_Wait;
	}*/
}
void Girl::StateWait() {
	if (--m_cnt <= 0) {
		m_cnt = rand() % 120 + 180;
		m_state = eState_Idle;
	}
}
void Girl::StateDamage() {
	m_img.ChangeAnimation(eAnimDamage,false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Girl::StateDown() {
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		m_img = COPY_RESOURCE("boseki", CImage);
		m_img.SetCenter(70, -40);
		m_img.SetSize(140, 140);
	}
}
void Girl::Update() {
	switch (m_state) {
	case eState_Idle:
		StateIdle();
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
	
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	m_vec.y += GRAVITY;
	m_pos += m_vec;
	
	m_img.UpdateAnimation();
	//ƒXƒNƒ[ƒ‹Ý’è
	m_scroll.x = m_pos.x - 1920 / 2;
}

void Girl::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}

void Girl::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Field:
		if (Field* f = dynamic_cast<Field*>(b)) {
			if (m_pos.y > f->GetGroundY()-200) {
				m_pos.y = f->GetGroundY()-200;
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;
	case eType_Wolf:
		if (Wolf* w = dynamic_cast<Wolf*>(b)) {
			if (Base::CollisionRect(this, w)) {
				if (m_damage_no != w->GetAttackNo() && Base::CollisionRect(this, w)) {
					//“¯‚¶UŒ‚‚Ì˜A‘±ƒ_ƒ[ƒW–hŽ~
					m_damage_no = w->GetAttackNo();
					hp -= 10;
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
	case eType_Bat:
		if (Bat* v = dynamic_cast<Bat*>(b)) {
			if (Base::CollisionRect(this, v)) {
				if (m_damage_no != v->GetAttackNo() && Base::CollisionRect(this, v)) {
					//“¯‚¶UŒ‚‚Ì˜A‘±ƒ_ƒ[ƒW–hŽ~
					m_damage_no = v->GetAttackNo();
					hp -= 10;
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
	case eType_Snake:
		if (Snake* s = dynamic_cast<Snake*>(b)) {
			if (Base::CollisionRect(this, s)) {
				if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
					//“¯‚¶UŒ‚‚Ì˜A‘±ƒ_ƒ[ƒW–hŽ~
					m_damage_no = s->GetAttackNo();
					hp -= 10;
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
	}
}