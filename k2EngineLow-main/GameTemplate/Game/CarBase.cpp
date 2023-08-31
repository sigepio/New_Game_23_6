#include "stdafx.h"
#include "CarBase.h"
#include "GameCamera.h"
#include "RightFrontWheel.h"
#include "FrontWheelBase.h"
#include "RightRearWheel.h"
#include "LeftRearWheel.h"
#include "TimeTrialMode.h"

bool CarBase::Start() {
	m_gamecamera = FindGO<GameCamera>("gamecamera");
	m_timetrialmode = FindGO<TimeTrialMode>("timetrialmode");
	m_frontwheelbase = NewGO<FrontWheelBase>(1, "frontwheelbase");

	m_rightrearwheel = NewGO< RightRearWheel>(2,"rightrearwheel");
	m_leftrearwheel = NewGO< LeftRearWheel>(2, "leftrearwheel");
	m_PlayerPosition.y -= 8.0f;
	return true;
}

CarBase::CarBase() {

}

CarBase::~CarBase() {

}


void CarBase::Update() {
	m_Throttle = m_frontwheelbase->Getm_Speed();
	m_PlayerForward = m_frontwheelbase->GetForward();

	if (m_LapState == 0 && m_frontwheelbase->GetPosition().x <= -5800.0f) {
		m_LapState++;
	}

	Move();
	Set();
}

void CarBase::Set() {
	//ƒJƒƒ‰
	m_gamecamera->SetTarget(m_frontwheelbase->GetPosition()+ m_PlayerPosition);
	m_timetrialmode->SetPosition(m_frontwheelbase->GetPosition() + m_PlayerPosition);
}

void CarBase::Move() {
	m_PlayerRotation = m_frontwheelbase->GetRotation();
	PlayerCarModel.SetRotation(m_frontwheelbase->GetRotation());
	PlayerCarModel.SetPosition(m_frontwheelbase->GetPosition()+ m_PlayerPosition);
	PlayerCarModel.Update();
}


void CarBase::Render(RenderContext& rc) {
	PlayerCarModel.Draw(rc);
}
