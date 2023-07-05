#pragma once

namespace nsK2EngineLow {
	//�f�B���N�V�������C�g�\����
	struct DirectionLight
	{
		Vector3 ligDirection;
		float pad0;
		Vector3 ligColor;
	};
	//�|�C���g���C�g�\����
	struct PointLight
	{
		Vector3 ligPosition;
		float pad0;
		Vector3 ligColor;
		float ligRange;
	};
	//�X�|�b�g���C�g�\����
	struct SpotLight
	{
		Vector3 ligPosition;
		float pad0;
		Vector3 ligColor;
		float ligRange;
		Vector3 ligDirection;
		float ligAngle;
	};

	//���C�g�\����
	struct Light
	{
		DirectionLight directionLight;	//�f�B���N�V�������C�g�̔z��
		float pad0;
		Vector3 eyePos;					//���_�̈ʒu
		float pad1;
		Vector3 ambientLight;			//����
		float pad2;
		//
		PointLight pointLight[10];		//�|�C���g���C�g�̔z��
		SpotLight spotLight[10];		//�X�|�b�g���C�g�̔z��
	};
	class SceneLight
	{
	public:
		//������
		void Init()
		{
			m_light.eyePos = g_camera3D->GetPosition();
		}

		void SetDirectionLight(Vector3 direction, Vector3 color)
		{
			m_light.directionLight.ligDirection = direction;
			m_light.directionLight.ligColor = color;
		}

		void SetPointLight(int num, Vector3 position, float range, Vector3 color)
		{
			m_light.pointLight[num].ligPosition = position;
			m_light.pointLight[num].ligRange = range;
			m_light.pointLight[num].ligColor = color;
		}
		void SetSpotLight(int num, Vector3 position, float range, Vector3 color, Vector3 direction, float angle)
		{
			m_light.spotLight[num].ligPosition = position;
			m_light.spotLight[num].ligRange = range;
			m_light.spotLight[num].ligColor = color;
			m_light.spotLight[num].ligDirection = direction;
			m_light.spotLight[num].ligAngle = angle;
		}
		Light& GetLight()
		{
			return m_light;
		}
	private:
		Light m_light;	//�V�[�����C�g
	};
}


