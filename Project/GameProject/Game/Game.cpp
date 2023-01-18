#include "Game.h"
#include "Field.h"
#include "../Object/Player.h"
#include "../Object/Enemy/Bat.h"
#include "../Object/Enemy/Wolf.h"
#include "../Object/Enemy/Snake.h"
#include"../Object/Player.h"
#include"../Object/Girl.h"
#include "Title.h"

Game::Game() :Base(eType_Scene)
{
	/*Base::Add(new Bat(CVector2D(2000, 300), true));
	Base::Add(new Snake(CVector2D(2000, 800), true));
	Base::Add(new Wolf(CVector2D(2400, 800), true));
	Base::Add(new Snake(CVector2D(2600, 800), true));

	Base::Add(new Bat(CVector2D(5100, 300), true));
	Base::Add(new Bat(CVector2D(5200, 300), true));
	Base::Add(new Snake(CVector2D(5300, 750), true));

	Base::Add(new Bat(CVector2D(6000, 300), true));
	Base::Add(new Wolf(CVector2D(6100, 750), true));
	Base::Add(new Snake(CVector2D(6200, 750), true));

	Base::Add(new Wolf(CVector2D(7000, 750), true));
	Base::Add(new Snake(CVector2D(7050, 750), true));
	Base::Add(new Bat(CVector2D(7100, 300), true));
	Base::Add(new Snake(CVector2D(7150, 750), true));
	Base::Add(new Snake(CVector2D(7200, 750), true));


	Base::Add(new Bat(CVector2D(-2000, 300), true));
	Base::Add(new Snake(CVector2D(-2000, 800), true));
	Base::Add(new Wolf(CVector2D(-2400, 800), true));
	Base::Add(new Snake(CVector2D(-2600, 800), true));

	Base::Add(new Bat(CVector2D(-5100, 300), true));
	Base::Add(new Bat(CVector2D(-5200, 300), true));
	Base::Add(new Snake(CVector2D(-5300, 750), true));

	Base::Add(new Bat(CVector2D(-6000, 300), true));
	Base::Add(new Wolf(CVector2D(-6100, 750), true));
	Base::Add(new Snake(CVector2D(-6200, 750), true));

	Base::Add(new Wolf(CVector2D(-7000, 750), true));
	Base::Add(new Snake(CVector2D(-7050, 750), true));
	Base::Add(new Bat(CVector2D(-7100, 300), true));
	Base::Add(new Snake(CVector2D(-7150, 750), true));
	Base::Add(new Snake(CVector2D(-7200, 750), true));
	*/

	m_img1 = COPY_RESOURCE("GameOver", CImage);
	m_img1.SetSize(636, 144);
	m_img1.SetPos(660, 480);

	m_img2 = COPY_RESOURCE("GameClear", CImage);
	m_img2.SetSize(712, 144);
	m_img2.SetPos(640, 480);
}
Game::~Game()
{
	Base::KillAll();
	Base::Add(new Title());
}

void Game::Update()
{
	if (!Base::FindObject(eType_Goal) && PUSH(CInput::eButton1)) {
		SetKill();
	}


	if (!Base::FindObject(eType_Player)) {
		SetKill();
	}
}

void Game::Draw()
{
	if (Girl* girl = dynamic_cast<Girl*>(Base::FindObject(eType_Girl)))
	{
		if (girl->GetState() == Girl::eState_Down) {
			m_img1.Draw();
		}
	}
	if (!Base::FindObject(eType_Goal)) {
		m_img2.Draw();
	}
}
