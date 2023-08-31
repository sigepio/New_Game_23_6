#include "stdafx.h"
#include "GameCamera.h"
#include "Car_RB6.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
GameCamera::GameCamera() {
	
}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{

	//視点を設定。
	//m_toCameraPos.Set(0.0f, 50.0f, -200.0f);
	m_toCameraPos.Set(0.0f, 0.0f, -5.0f);
	//プレイヤーのインスタンスを探す。
	m_carbase = FindGO<Car_RB6>("car_rb6");

	//カメラのニアクリップとファークリップを設定する。
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(80000.0f);

	return true;
}

void GameCamera::Update() {
	//カメラを更新。
	//注視点を計算する。
	//m_target = m_carbase->GetPosition();
	//プレイヤの足元からちょっと上を注視点とする。
	m_target.y += 50.0f;

	if (m_carbase->Returnm_throttle() != 0.0f) {
		Vector3 toCameraPosOld = m_toCameraPos;
		//パッドの入力を使ってカメラを回す。
		float x = g_pad[0]->GetLStickXF();
		float y = g_pad[0]->GetRStickYF();
		//Y軸周りの回転
		Quaternion qRot;
		qRot.SetRotationDeg(Vector3::AxisY, 2.87f * x);
		qRot.Apply(m_toCameraPos);
		//X軸周りの回転。
		Vector3 axisX;
		axisX.Cross(Vector3::AxisY, m_toCameraPos);
		axisX.Normalize();
		qRot.SetRotationDeg(axisX, 1.3f * y);
		qRot.Apply(m_toCameraPos);
		//カメラの回転の上限をチェックする。
		//注視点から視点までのベクトルを正規化する。
		//正規化すると、ベクトルの大きさが１になる。
		//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
		Vector3 toPosDir = m_toCameraPos;
		toPosDir.Normalize();
		if (toPosDir.y < -0.2f) {
			//カメラが上向きすぎ。
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.9f) {
			//カメラが下向きすぎ。
			m_toCameraPos = toCameraPosOld;
		}
	}
	//視点を計算する。
	/*Quaternion m_CameraRot;
	float Angle = (std::acos(m_toCameraPos.Dot(m_carbase->GetForward()) / (m_toCameraPos.Length() * m_carbase->GetForward().Length()))) * 180.0 / M_PI;
	m_CameraRot.SetRotationDegY(Angle);
	m_CameraRot.Apply(m_toCameraPos);
	*/

	Vector3 pos = m_target + m_toCameraPos;
	//メインカメラに注視点と視点を設定する。
	g_camera3D->SetTarget(m_target);
	g_camera3D->SetPosition(pos);

	//カメラの更新。
	g_camera3D->Update();
}