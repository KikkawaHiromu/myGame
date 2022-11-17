#pragma once
#include <GLLibrary.h>
#define GRAVITY (9.8f/20)
enum {
	eType_Title,
	eType_Field,
	eType_Girl,
	eType_Player,
	eType_UI,
};

class Base {
public:
	int m_type;
	CVector2D m_pos;
	CVector2D m_pos_old;
	CVector2D m_vec;
	float m_rad;
	float m_ang;
	static std::list<Base*> m_list;
	bool m_kill;
	static CVector2D m_scroll;
	CRect	m_rect;
	double distance;
	int have_distance;

public:
	static CVector2D GetScreenPos(const CVector2D& pos);
	//type �I�u�W�F�N�g�̎��
	Base(int type);
	virtual ~Base();
	virtual void Update();
	virtual void Draw();
	virtual void Collision(Base* b);
	//�폜�t���OON
	void SetKill() { m_kill = true; }
	//�S�ẴI�u�W�F�N�g�̍X�V
	static void UpdateAll();
	//�S�ẴI�u�W�F�N�g�̕`��
	static void DrawAll();
	//�S�ẴI�u�W�F�N�g�̓����蔻�茟��
	static void CollisionAll();
	//�폜�`�F�b�N
	static void CheckKillAll();
	//�I�u�W�F�N�g�̒ǉ�
	static void Add(Base* b);
	static void KillAll();
	//�~���m�̏Փ�
	static bool CollisionCircle(Base* b1, Base* b2);
	//��`���m�̔���
	static bool CollisionRect(Base* b1, Base* b2);
	/// ��`�̕\��
	void DrawRect();

	static Base* FindObject(int type);
	static std::list<Base*> FindObjects(int type);

};

