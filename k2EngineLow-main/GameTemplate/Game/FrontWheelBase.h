#pragma once
#include "sound/SoundEngine.h"
class RightFrontWheel;
class LeftFrontWheel;

class FrontWheelBase:public IGameObject,Noncopyable
{
public:
	FrontWheelBase();
	~FrontWheelBase();
	bool Start();
	void Update();
	void Move();
	float Acceleration();
	void Handling();
	void Render(RenderContext&rc);

	//�擾�n�֐�

	//�|�W�V�����̎擾
	Vector3 GetPosition() {
		return m_FrontWheelPosition;
	}

	//��]���̎擾
	Quaternion  GetRotation() {
		return m_FrontWheelRotation;
	}

	Vector3 GetForward() {
		return m_FrontWheelForward;
	}

	float Getm_Speed() {
		return RSpeed;
	}

	

	//�ݒ�n�֐�

	//�|�W�V�����̐ݒ�
	void SetPosition(Vector3 position) {
		m_FrontWheelPosition = position;
	}

	//�v���C���[�̉�]�͂̐ݒ�
	void SetPlayerRotation(Quaternion rotation) {
		OriginRotation = rotation;
	}

	void SetForward(Vector3 forward) {
		m_FrontWheelForwardCatch = forward;
	}

protected:
	Vector3 m_FrontWheelPosition = Vector3::Zero;
	Vector3 m_LocalPosition;
	Vector3 m_FrontWheelForward = { 0.0f,0.0f,1.0f };
	Vector3 m_FrontWheelForwardCatch = { 0.0f,0.0f,1.0f };
	Vector3 LsatStickL;
	Vector3 m_MoveSpeed;
	Vector3 gearposition;
	Vector3 speedposition;
	Vector3 meterposition;

	Quaternion OriginRotation;
	Quaternion m_FrontWheelRotation;
	Quaternion m_FrontWheelLocalRotation;
	Quaternion needlerot;
	Quaternion speedneedlerot;

	CharacterController m_characterController;		//�L�����N�^�[�R���g���[���[

	ModelRender m_FrontWheelModel;

	SpriteRender meterRender;
	SpriteRender speedRender;
	SpriteRender gearRender;
	SpriteRender needleRender;
	SpriteRender speedneedleRender;

	SoundSource* engine;
	SoundSource* engine_s;

	RightFrontWheel* m_rightfrontwheel;
	LeftFrontWheel* m_leftfrontwheel;

	bool TurnRightState = false;

	float m_throttle;
	float m_brake;
	float m_accelerator;
	float m_move;


	float Speed = 0.0f;								//����
	float RSpeed = 0.0f;							//���^�[�����ꂽ���x
	float Rotation_Speed = 0.0f;					//�G���W����]��
	float e_s = 1;
	
	int Gear = 1;									//�M�A
};

