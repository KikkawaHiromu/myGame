#include "Title.h"
#include "Game.h"

Title::Title() :Base(eType_Title),
m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
	m_img = COPY_RESOURCE("Title", CImage);
}

Title::~Title()
{
	//全てのオブジェクトを破棄
	Base::KillAll();
	//ゲームシーンへ
	Base::Add(new Game());
}
void Title::Update()
{
	//ボタン１でタイトル破棄
	if (PUSH(CInput::eButton1)) {
		SetKill();
	}
}

void Title::Draw()
{
	m_img.Draw();
	//文字表示
	m_title_text.Draw(650, 500, 255, 255, 0, "「送り火の道」");
	m_title_text.Draw(700, 700, 255, 255, 1, "");
	m_title_text.Draw(800, 800, 255, 255, 1, "[Z]で開始");
}