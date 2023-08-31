#include "stdafx.h"
#include "RightFrontWheel.h"
#include "FrontWheelBase.h"
RightFrontWheel::RightFrontWheel() {
	m_FrontWheelModel.Init("Assets/modelData/Car/tire2.tkm");

	m_LocalPosition = { 30.0f,5.0f,55.0f };
}
RightFrontWheel::~RightFrontWheel() {

}

bool RightFrontWheel::Start() {
	m_frontwheelbase = FindGO<FrontWheelBase>("frontwheelbase");
	return true;
}

void RightFrontWheel::Update() {

	//���[�J���|�W�V������������
	Vector3 lp = m_LocalPosition;


	//�v���C���[�̉�]�ʂ�������
	Quaternion originRotation = m_frontwheelbase->GetRotation();


	//�v���C���[�̃|�W�V������������
	m_FrontWheelPosition = m_frontwheelbase->GetPosition();


	//��Z
	originRotation.Multiply(lp);


	//�|�W�V�����Ƀ��[�J���|�W�V�����𑫂�
	m_FrontWheelPosition += lp;


	//�ŏI�I�ȉ�]�ʂ�������
	m_FrontWheelRotation = originRotation;

	
	m_FrontWheelModel.SetPosition(m_FrontWheelPosition);
	m_FrontWheelModel.SetRotation(m_FrontWheelRotation);
	m_FrontWheelModel.Update();

	//Move();
	Rotation();
}

void RightFrontWheel::Move() {
	//�X�e�B�b�N��|�����ʂ̎擾
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();

	Vector3 WheelRemit = Calc(m_FrontWheelLocalRotation);

	if (g_pad[0]->GetLStickXF() != 0.0f) {
		Vector3 FlontWheelAngle = Calc(m_FrontWheelLocalRotation);
		if (stickL.x > 0.0f) {
			if (stickL.x < LsatStickL.x) {
				if (FlontWheelAngle.y <= stickL.x * 30.0f) {
					m_FrontWheelForward.x = m_FrontWheelForwardCatch.x * cos(stickL.x * 0.01) - m_FrontWheelForwardCatch.z * sin(stickL.x * 0.01);
					m_FrontWheelForward.z = m_FrontWheelForwardCatch.x * sin(stickL.x * 0.01) + m_FrontWheelForwardCatch.z * cos(stickL.x * 0.01);

					m_FrontWheelLocalRotation.SetRotationY(atan2(m_FrontWheelForward.x, m_FrontWheelForward.z));
				}
			}
			else {
				if (FlontWheelAngle.y >= stickL.x * -30.0f && FlontWheelAngle.y <= stickL.x * 30.0f) {
					m_FrontWheelForward.x = m_FrontWheelForwardCatch.x * cos(stickL.x * -0.05) - m_FrontWheelForwardCatch.z * sin(stickL.x * -0.05);
					m_FrontWheelForward.z = m_FrontWheelForwardCatch.x * sin(stickL.x * -0.05) + m_FrontWheelForwardCatch.z * cos(stickL.x * -0.05);

					m_FrontWheelLocalRotation.SetRotationY(atan2(m_FrontWheelForward.x, m_FrontWheelForward.z));
				}
			}
		}
		else {
			if (stickL.x > LsatStickL.x) {
				if (FlontWheelAngle.y >= stickL.x * 30.0f) {
					m_FrontWheelForward.x = m_FrontWheelForwardCatch.x * cos(stickL.x * 0.01) - m_FrontWheelForwardCatch.z * sin(stickL.x * 0.01);
					m_FrontWheelForward.z = m_FrontWheelForwardCatch.x * sin(stickL.x * 0.01) + m_FrontWheelForwardCatch.z * cos(stickL.x * 0.01);

					m_FrontWheelLocalRotation.SetRotationY(atan2(m_FrontWheelForward.x, m_FrontWheelForward.z));
				}
			}
			else {
				if (FlontWheelAngle.y <= stickL.x * -30.0f && FlontWheelAngle.y >= stickL.x * 30.0f) {
					m_FrontWheelForward.x = m_FrontWheelForwardCatch.x * cos(stickL.x * -0.05) - m_FrontWheelForwardCatch.z * sin(stickL.x * -0.05);
					m_FrontWheelForward.z = m_FrontWheelForwardCatch.x * sin(stickL.x * -0.05) + m_FrontWheelForwardCatch.z * cos(stickL.x * -0.05);

					m_FrontWheelLocalRotation.SetRotationY(atan2(m_FrontWheelForward.x, m_FrontWheelForward.z));
				}
			}
		}
		m_FrontWheelRotation *= m_FrontWheelLocalRotation;
		m_FrontWheelModel.SetPosition(m_FrontWheelPosition);
		m_FrontWheelModel.SetRotation(m_FrontWheelRotation);
		m_FrontWheelModel.Update();

	}
	else {
		m_FrontWheelLocalRotation = m_FrontWheelRotation;
		m_FrontWheelForward = m_FrontWheelForwardCatch;
	}



	LsatStickL.x = stickL.x;
}

void RightFrontWheel::Rotation() {
	if (m_frontwheelbase->Getm_Speed() != 0) {
		m_FrontWheelRightRotation.AddRotationDegX(m_frontwheelbase->Getm_Speed());
		m_FrontWheelRotation *= m_FrontWheelRightRotation;
		m_FrontWheelModel.SetRotation(m_FrontWheelRotation);
		m_FrontWheelModel.Update();
	}
}

void RightFrontWheel::Render(RenderContext& rc) {
	m_FrontWheelModel.Draw(rc);
}