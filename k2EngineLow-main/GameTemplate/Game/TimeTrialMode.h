#pragma once


class Lighting;
class GameCamera;
class BackGround;
class Car_RB6;


class TimeTrialMode:public IGameObject,Noncopyable
{
public:
	TimeTrialMode();
	~TimeTrialMode();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetPosition(Vector3 position) {
		m_NowPPosition = position;
	}
private:

	Vector3 m_NowPPosition=Vector3::Zero;
	Vector3 m_TimeUIPosition=Vector3::Zero;
	Vector3 m_FastestLapsPosition = Vector3::Zero;
	Lighting* m_lighting;
	GameCamera* m_gamecamera;
	BackGround* m_background;
	Car_RB6* m_RB6;
	SkyCube* m_skyCube = nullptr;

	ModelRender StartRender;
	SpriteRender TimeUIRender;
	SpriteRender FastestLapsRender;
	FontRender TimeFont;
	FontRender FTimeFont;


	
	float m_LapTimeminsec;
	float m_timer;
	float m_timersecont;
	
	float FastestLap=10000.0f;

	float FastestLapTimesec = 60.0f;

	std::vector<float> LapTimeList;


	int m_timerminit;
	int m_LapTimemin;
	int FastestLapTimemin = 10000;
	int m_skyCubeType = enSkyCubeType_Day;
	int LapCount = 0;
	int m_FirstFrame = 0;

};

