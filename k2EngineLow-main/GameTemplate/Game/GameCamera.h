#pragma once
class Car_RB6;

class GameCamera:public IGameObject,Noncopyable
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	/// <summary>
	/// �^�[�Q�b�g���Z�b�g����
	/// </summary>
	/// <param name="target">�^�[�Q�b�g</param>
	void SetTarget(Vector3 target) {
		m_target = target;
	}

	/// <summary>
	/// �J�����̃|�W�V������Ԃ�
	/// </summary>
	/// <returns>�J�����̃|�W�V����</returns>
	Vector3 GetCameraPos() const
	{
		return m_position;
	}

	/// <summary>
	/// �J�����̑O������Ԃ�
	/// </summary>
	/// <returns>�J�����̑O����</returns>
	Vector3 GetCameraForward() const
	{
		return m_cameraForward;
	}

private:
	/////////////////////////////////////
	//�����o�ϐ�
	/////////////////////////////////////
	Car_RB6* m_carbase;

	Vector3 m_position = Vector3::Zero;
	Vector3 m_cameraForward = { 0.0f,0.0f,1.0f };
	Vector3 m_toCameraPos = Vector3::Zero;			//�����_���王�_�Ɍ������x�N�g��
	Vector3 m_target = Vector3::Zero;


};
