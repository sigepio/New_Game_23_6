#include "stdafx.h"
#include "Lighting.h"
#include "Car_RB6.h"

Lighting::Lighting() {

}

Lighting::~Lighting() {

}

bool Lighting::Start() {
	

	//ライト方向の正規化
	Light_Direction.Normalize();
	//ディレクションライトの設定
	RenderingEngine::GetInstance()->SetDirectionLight(Light_Direction, Light_Color);

	

	return true;
}

void Lighting::Update() {

}