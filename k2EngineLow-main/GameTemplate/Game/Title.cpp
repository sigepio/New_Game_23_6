#include "stdafx.h"
#include "Title.h"
#include "Menu.h"
Title::Title() {

}
Title::~Title() {

}
bool Title::Start() {
	m_TitleSprite.Init("Assets/sprite/Title/Title_Logo.DDS", 960.0f, 540.0f);
	m_PressStartSprite.Init("Assets/sprite/Title/Press_any_button.DDS", 1920.0f, 1080.0f);
	m_PressStartSprite.SetMulColor(m_PressStartSpriteColor);
	return true;
}
void Title::Update() {
	if (m_PressColorTime % 100 == 0) {
		m_PressDirection *= -1;
	}
	
	m_PressStartSpriteColor.w -= 0.01 * m_PressDirection;
	m_PressStartSprite.SetMulColor(m_PressStartSpriteColor);
	
	if (g_pad[0]->IsTrigger(enButtonA)) {
		Menu *m_menu = NewGO<Menu>(1, "menu");
		DeleteGO(this);
	}
	m_PressColorTime++;
	m_PressStartSprite.Update();
}
void Title::Render(RenderContext& rc) {
	m_TitleSprite.Draw(rc);
	m_PressStartSprite.Draw(rc);
}