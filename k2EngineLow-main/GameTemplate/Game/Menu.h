#pragma once
class TimeTrialMode;

class Menu:public IGameObject,Noncopyable
{
public:
	Menu();
	~Menu();
	bool Start();
	void Update();
	
	void Render(RenderContext& rc);

private:
	TimeTrialMode* m_timetrialmode;

	int SelectNow = 0;		//0:TA 1:GT 2:Option
};

