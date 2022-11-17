#include"Girl.h"
#include"../Game/Field.h"

Girl::Girl(const CVector2D& p, bool flip):
	Base(eType_Girl){
	m_img = COPY_RESOURCE("è≠èó_í èÌ", CImage);
	m_pos = p;
	m_img.SetCenter(80,160);
	m_img.SetSize(160, 320);
	m_rect = CRect(-80, -160, 80, 160);
	m_flip = flip;
	m_is_ground;
	m_state = eState_Idle;
	m_damage_no = -1;
	m_cnt = 200;
}

void Girl::StateIdle() {
	const float move_speed = 3;
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
void Girl::StateFound() {

}
void Girl::StateCry() {

}
void Girl::StateDamage() {

}
void Girl::StateDown() {

}
void Girl::Update() {
	switch (m_state) {
	case eState_Idle:
		StateIdle();
		break;
	case eState_Wait:
		StateWait();
		break;
	case eState_Found:
		StateFound();
		break;
	case eState_Cry:
		StateCry();
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
	//ÉXÉNÉçÅ[Éãê›íË
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
			if (m_pos.y > f->GetGroundY()) {
				m_pos.y = f->GetGroundY();
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;
	}
}