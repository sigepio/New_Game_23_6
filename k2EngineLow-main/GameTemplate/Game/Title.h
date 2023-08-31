#pragma once
class SoundManage;
class Menu;

class Title:public IGameObject,Noncopyable
{
public:
	Title();
	~Title();
	void Update();
	bool Start();
	void Render(RenderContext&rc);
	
private:
	

	SpriteRender m_TitleSprite;
	SpriteRender m_PressStartSprite;

	Vector4 m_PressStartSpriteColor = { 1.0f,1.0f,1.0f,1.0f };
	
	int m_PressColorTime=0;
	int m_PressDirection=1;
};

