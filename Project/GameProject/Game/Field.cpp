#include"Field.h"
Field::Field() :Base(eType_Field) {
	m_map01 = COPY_RESOURCE("m_map01", CImage);

	m_ground_y = 930;
}
void Field::Draw() {
	float sc;
	sc = m_scroll.x;
	m_map01.SetRect(sc, 0, sc + 1920, 1080);
	m_map01.Draw();
	m_map01.SetSize(1920, 1080);
}