#pragma once
class GameCamera;
class RightFrontWheel;
class FrontWheelBase;
class RightRearWheel;
class LeftRearWheel;
class TimeTrialMode;

class CarBase:public IGameObject,Noncopyable
{
public:
	CarBase();
	~CarBase();
	bool Start();
	void Update();
	
	void Move();
	void Set();
	void Render(RenderContext& rc);


	//取得系関数
	
	//プレイヤーポジションの取得
	Vector3 GetPosition() const {
		return m_PlayerPosition;
	}

	//プレイヤーローテーションの取得
	Quaternion GetRotation() {
		return m_PlayerRotation;
	}

	Vector3 GetForward() {
		return m_PlayerForward;
	}

	int Getm_LapState() {
		return m_LapState;
	}

	//設定系関数

	//プレイヤーポジションの設定
	void SetPosition(Vector3 Potion) {
		m_PlayerPosition = Potion;
	}

	//プレイヤーローテーションの設定
	void SetRotation(Quaternion Rotation) {
		m_PlayerRotation = Rotation;
	}

	void Setm_LapState(int LapState) {
		m_LapState = LapState;
	}

	//その他の関数
	float Returnm_throttle() {
		return m_Throttle;
	}

	
protected:
	Vector3 m_PlayerPosition=Vector3::Zero;			//プレイヤーポジション
	Vector3 m_PlayerForward = { 0.0f, 0.0f, 1.0f };	//プレイヤーの正面ベクトル
	Vector3 m_PlayerMoveSpeed = Vector3::Zero;		//プレイヤーの移動速度

	Quaternion m_PlayerRotation;					//プレイヤーローテーション

	float m_Acceleration=0.0f;
	float m_Throttle = 0.0f;

	ModelRender PlayerCarModel;

	TimeTrialMode* m_timetrialmode;
	GameCamera*m_gamecamera=nullptr;
	RightFrontWheel* m_rightfrontwheel=nullptr;
	FrontWheelBase* m_frontwheelbase = nullptr;
	RightRearWheel* m_rightrearwheel = nullptr;
	LeftRearWheel* m_leftrearwheel = nullptr;

	int m_LapState = 0;
};

