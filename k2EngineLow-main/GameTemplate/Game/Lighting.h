#pragma once
class Car_RB6;
class Lighting:public IGameObject,Noncopyable
{
public:
	Lighting();
	~Lighting();
	bool Start();
	void Update();
private:
	Vector3 Light_Direction = { 0.0f,-1.0f,0.0f };
	Vector3 Light_Color = { 1.0f,1.0f,1.0f };

	Car_RB6* m_rb6;
};

