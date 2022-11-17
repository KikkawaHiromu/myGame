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
	//type オブジェクトの種類
	Base(int type);
	virtual ~Base();
	virtual void Update();
	virtual void Draw();
	virtual void Collision(Base* b);
	//削除フラグON
	void SetKill() { m_kill = true; }
	//全てのオブジェクトの更新
	static void UpdateAll();
	//全てのオブジェクトの描画
	static void DrawAll();
	//全てのオブジェクトの当たり判定検証
	static void CollisionAll();
	//削除チェック
	static void CheckKillAll();
	//オブジェクトの追加
	static void Add(Base* b);
	static void KillAll();
	//円同士の衝突
	static bool CollisionCircle(Base* b1, Base* b2);
	//矩形同士の判定
	static bool CollisionRect(Base* b1, Base* b2);
	/// 矩形の表示
	void DrawRect();

	static Base* FindObject(int type);
	static std::list<Base*> FindObjects(int type);

};

