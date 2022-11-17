#pragma once
#include"../Base/Base.h"
class Field :public Base {
private:
	CImage m_map01;

	float m_ground_y;
public:
	Field();
	void Draw();
	float GetGroundY() {
		return m_ground_y;
	}
};