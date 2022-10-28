#include "../Base/Base.h"
std::list<Base*> Base::m_list;
//�X�N���[���l�̒�`
CVector2D Base::m_scroll(0, 0);

CVector2D Base::GetScreenPos(const CVector2D& pos)
{
	return pos - m_scroll;
}
Base::Base(int type) :m_type(type),m_kill(false), m_vec(0,0),m_pos(0,0) {

}
Base::~Base() {

}
void Base::Update() {

}
void Base::Draw() {

}
void Base::Collision(Base* b)
{
}
void Base::UpdateAll()
{
	//�S�I�u�W�F�N�g�̍X�V
	for (auto& b : m_list) {
		b->Update();
	}
}

void Base::DrawAll()
{
	//�S�I�u�W�F�N�g�̕`�揈��
	for (auto& b : m_list) {
		b->Draw();
	}
}

void Base::CollisionAll()
{
	auto it1 = m_list.begin();
	auto last = m_list.end();
	while (it1 != last) {
		auto it2 = it1;
		it2++;
		while (it2 != last) {
			(*it1)->Collision(*it2);
			(*it2)->Collision(*it1);
			it2++;
		}
		it1++;
	}
}
void Base::CheckKillAll()
{
	auto it = m_list.begin();
	auto last = m_list.end();
	while (it != last) {
		if ((*it)->m_kill) {
			delete (*it);
			it = m_list.erase(it);
		}
		else {
			//����
			it++;
		}
	}
}



void Base::Add(Base* b)
{
	//Type���ɂ��\�[�g
	auto itr = m_list.begin();
	//�����܂ŌJ��Ԃ�
	while (itr != m_list.end()) {
		//�ǉ��I�u�W�F�N�g���type�̒l���傫���I�u�W�F�N�g����������
		if ((*itr)->m_type > b->m_type) {
			//�����ɑ}��(�O�ɑ}�������)
			m_list.insert(itr, b);
			return;
		}
		itr++;
	}
	//�I�u�W�F�N�gb�𖖔��ɒǉ�
	m_list.push_back(b);
}
void Base::KillAll()
{
	std::list<Base*> ret;
	for (auto& b : m_list) {
		b->m_kill = true;
	}
}
bool Base::CollisionCircle(Base* b1, Base* b2)
{
	CVector2D v = b1->m_pos - b2->m_pos;
	float l = v.Length();
	return false;
}
Base* Base::FindObject(int type)
{
	auto it = m_list.begin();
	auto last = m_list.end();
	while (it != last) {
		if ((*it)->m_type == type) {
			return (*it);
		}
		it++;
	}
	return nullptr;
}

std::list<Base*> Base::FindObjects(int type)
{
	std::list<Base*> ret;
	for (auto& b : m_list) {
		if (b->m_type == type)
			ret.push_back(b);
	}
	return ret;
}

void Base::DrawRect()
{
	//�f�o�b�O�p�@��`�̕\��
	CRect rect = CRect(
		m_pos.x + m_rect.m_left,
		m_pos.y + m_rect.m_top,
		m_pos.x + m_rect.m_right,
		m_pos.y + m_rect.m_bottom);
	Utility::DrawQuad(
		CVector2D(rect.m_left, rect.m_top) - m_scroll,
		CVector2D(rect.m_width, rect.m_height),
		CVector4D(1, 0, 0, 0.5f));
}
bool Base::CollisionRect(Base* b1, Base* b2)
{
	//b1�̋�`
	CRect rect1 = CRect(
		b1->m_pos.x + b1->m_rect.m_left,
		b1->m_pos.y + b1->m_rect.m_top,
		b1->m_pos.x + b1->m_rect.m_right,
		b1->m_pos.y + b1->m_rect.m_bottom);
	//b2�̋�`
	CRect rect2 = CRect(
		b2->m_pos.x + b2->m_rect.m_left,
		b2->m_pos.y + b2->m_rect.m_top,
		b2->m_pos.x + b2->m_rect.m_right,
		b2->m_pos.y + b2->m_rect.m_bottom);

	//��`���m�̔���
	if (rect1.m_left <= rect2.m_right && rect1.m_right >= rect2.m_left &&
		rect1.m_top <= rect2.m_bottom && rect1.m_bottom >= rect2.m_top)
		return true;

	return false;
}