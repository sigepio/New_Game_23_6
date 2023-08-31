#include "stdafx.h"
#include "TimeTrialMode.h"
#include "Lighting.h"
#include "GameCamera.h"
#include "Car_RB6.h"
#include "BackGround.h"
#include "FrontWheelBase.h"
#include <vector>


TimeTrialMode::TimeTrialMode() {

}

TimeTrialMode::~TimeTrialMode() {

}

bool TimeTrialMode::Start() {
	
	// åªç›ÇÃãÛÇîjä¸ÅB
	DeleteGO(m_skyCube);
	m_skyCube = NewGO<SkyCube>(0, "skycube");

	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);
	m_skyCube->SetScale(4000.0f);

	m_background = NewGO<BackGround>(1, "background");
	m_gamecamera = NewGO<GameCamera>(0, "gamecamera");

	m_RB6 = NewGO<Car_RB6>(2, "car_rb6");
	m_lighting = NewGO<Lighting>(0, "lighting");

	TimeUIRender.Init("Assets/sprite/TimeUi.DDS", 1920.0f, 1080.0f);
	m_TimeUIPosition.y = -48.0f;
	TimeUIRender.SetPosition(m_TimeUIPosition);
	TimeUIRender.Update();

	FastestLapsRender.Init("Assets/sprite/FastestLap.DDS", 1632.0f, 918.0f);
	m_FastestLapsPosition = { Vector3(700.0f, 360.0f, 0.0f) };
	FastestLapsRender.SetPosition(m_FastestLapsPosition);
	FastestLapsRender.Update();

	StartRender.Init("Assets/modelData/course/track1.tkm", false);
	
	return true;
}

void TimeTrialMode::Update() {
		
	//éûä‘åoâﬂ
	m_timer += g_gameTime->GetFrameDeltaTime();

	
	if (m_timer >= 60.0f) {
		m_timerminit ++;
		m_timer =0;
	}
	m_timersecont = m_timer;
	

	wchar_t Time[256];
	swprintf_s(Time, 256, L"%d:%.3f\n", m_timerminit,m_timersecont);
	TimeFont.SetPosition(-50.0f, 300.0f, 0.0f);
	

	TimeFont.SetText(Time);

	if (m_RB6->Getm_LapState() == 1 && m_NowPPosition.z >= 0.0f&& m_NowPPosition.x>-100.0f) {
		if (FastestLap >= m_timerminit*60+m_timersecont) {
			FastestLap = m_timerminit * 60 + m_timersecont;
			FastestLapTimemin = m_timerminit;
			FastestLapTimesec = m_timersecont;
		}
		m_timer = 0.0f;
		m_timerminit = 0.0f;
		m_RB6->Setm_LapState(0);
		LapCount++;
		
		wchar_t FTime[256];
		swprintf_s(FTime, 256, L"%d:%.3f\n", FastestLapTimemin, FastestLapTimesec);
		FTimeFont.SetPosition(750.0f, 500.0f, 0.0f);


		FTimeFont.SetText(FTime);

	}

	

	m_FirstFrame++;
}

void TimeTrialMode::Render(RenderContext& rc) {
	
	StartRender.Draw(rc);
	TimeUIRender.Draw(rc);
	FastestLapsRender.Draw(rc);
	FTimeFont.Draw(rc);
	TimeFont.Draw(rc);
}