#include"Girl.h"

Girl::Girl(const CVector2D& p, bool flip):
	Base(eType_Girl){
	m_img = COPY_RESOURCE("Girl", CImage);
	m_pos = p;
	m_img.SetCenter(80,160);
	m_img.SetSize(160, 320);
	m_rect = CRect(-80, -160, 80, 160);
	m_flip = flip;
	m_state = eState_Idle;
	m_damage_no = -1;
}

void Girl::StateIdle() {

}
void Girl::StateWait() {

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
}

void Girl::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}

void Girl::Collision(Base* b) {
}