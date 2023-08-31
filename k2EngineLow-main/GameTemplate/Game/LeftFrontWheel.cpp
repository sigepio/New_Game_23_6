#include "stdafx.h"
#include "LeftFrontWheel.h"
#include "FrontWheelBase.h"

LeftFrontWheel::LeftFrontWheel() {
	m_FrontWheelModel.Init("Assets/modelData/Car/tire.tkm");

	m_LocalPosition = { -30.0f,5.0f,55.0f };
}

LeftFrontWheel::~LeftFrontWheel() {

}

bool LeftFrontWheel::Start() {
	m_frontwheelbase = FindGO<FrontWheelBase>("frontwheelbase");
	return true;
}

void LeftFrontWheel::Update() {
	//ローカルポジションを教える
	Vector3 lp = m_LocalPosition;


	//プレイヤーの回転量を教える
	Quaternion originRotation = m_frontwheelbase->GetRotation();


	//プレイヤーのポジションを教える
	m_FrontWheelPosition = m_frontwheelbase->GetPosition();


	//乗算
	originRotation.Multiply(lp);


	//ポジションにローカルポジションを足す
	m_FrontWheelPosition += lp;


	//最終的な回転量を教える
	m_FrontWheelRotation = originRotation;


	m_FrontWheelModel.SetPosition(m_FrontWheelPosition);
	m_FrontWheelModel.SetRotation(m_FrontWheelRotation);
	m_FrontWheelModel.Update();

	//Move();
	Rotation();
}

void LeftFrontWheel::Move() {
	//スティックを倒した量の取得
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

void LeftFrontWheel::Rotation() {
	if (m_frontwheelbase->Getm_Speed() != 0) {
		m_FrontWheelLeftRotation.AddRotationDegX(m_frontwheelbase->Getm_Speed());
		m_FrontWheelRotation *= m_FrontWheelLeftRotation;
		m_FrontWheelModel.SetRotation(m_FrontWheelRotation);
		m_FrontWheelModel.Update();
	}
}

void LeftFrontWheel::Render(RenderContext& rc) {
	m_FrontWheelModel.Draw(rc);
}
