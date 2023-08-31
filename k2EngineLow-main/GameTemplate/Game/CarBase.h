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


	//�擾�n�֐�
	
	//�v���C���[�|�W�V�����̎擾
	Vector3 GetPosition() const {
		return m_PlayerPosition;
	}

	//�v���C���[���[�e�[�V�����̎擾
	Quaternion GetRotation() {
		return m_PlayerRotation;
	}

	Vector3 GetForward() {
		return m_PlayerForward;
	}

	int Getm_LapState() {
		return m_LapState;
	}

	//�ݒ�n�֐�

	//�v���C���[�|�W�V�����̐ݒ�
	void SetPosition(Vector3 Potion) {
		m_PlayerPosition = Potion;
	}

	//�v���C���[���[�e�[�V�����̐ݒ�
	void SetRotation(Quaternion Rotation) {
		m_PlayerRotation = Rotation;
	}

	void Setm_LapState(int LapState) {
		m_LapState = LapState;
	}

	//���̑��̊֐�
	float Returnm_throttle() {
		return m_Throttle;
	}

	
protected:
	Vector3 m_PlayerPosition=Vector3::Zero;			//�v���C���[�|�W�V����
	Vector3 m_PlayerForward = { 0.0f, 0.0f, 1.0f };	//�v���C���[�̐��ʃx�N�g��
	Vector3 m_PlayerMoveSpeed = Vector3::Zero;		//�v���C���[�̈ړ����x

	Quaternion m_PlayerRotation;					//�v���C���[���[�e�[�V����

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

