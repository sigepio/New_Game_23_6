#pragma once
class FrontWheelBase;

class LeftFrontWheel:public IGameObject, Noncopyable
{
public:
	LeftFrontWheel();
	~LeftFrontWheel();
	bool Start();
	void Update();
	void Move();
	void Rotation();
	void Render(RenderContext& rc);

	void SetForward(Vector3 forward) {
		m_FrontWheelForwardCatch = forward;
	}
private:
	Vector3 m_FrontWheelPosition = Vector3::Zero;
	Vector3 m_LocalPosition;
	Vector3 m_FrontWheelForward = { 0.0f,0.0f,1.0f };
	Vector3 m_FrontWheelForwardCatch = { 0.0f,0.0f,1.0f };
	Vector3 LsatStickL;

	Quaternion OriginRotation;
	Quaternion m_FrontWheelRotation;
	Quaternion m_FrontWheelLocalRotation;
	Quaternion m_FrontWheelLeftRotation;


	ModelRender m_FrontWheelModel;

	FrontWheelBase* m_frontwheelbase;
};

