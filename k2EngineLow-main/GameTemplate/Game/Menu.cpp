#include "stdafx.h"
#include "Menu.h"
#include "TimeTrialMode.h"

Menu::Menu() {

}

Menu::~Menu() {

}
bool Menu::Start() {
	m_timetrialmode = NewGO<TimeTrialMode>(0, "timetrialmode");
	DeleteGO(this);
	return true;
}

void Menu::Update() {
	if (g_pad[0]->IsTrigger(enButtonA)) {
		switch (SelectNow)
		{
		case 0:
			
			break;
		default:
			break;
		}
	}
}

void Menu::Render(RenderContext& rc) {

}