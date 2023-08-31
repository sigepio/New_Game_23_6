#include "stdafx.h"
#include "Test.h"
#include "BackGround.h"

Test::Test() {
	bg = NewGO<BackGround>(0, "background");

	//ライト方向の正規化
	Light_Direction.Normalize();
	//ディレクションライトの設定
	RenderingEngine::GetInstance()->SetDirectionLight(Light_Direction, Light_Color);

	RenderingEngine::GetInstance()->SetPointLight(0, {0.0f,50.0f,50.0f}, 100.0f, {15.0f,0.0f,0.0f});
	
	RenderingEngine::GetInstance()->SetSpotLight(0, { 0.0f,70.0f,0.0f }, 10.0f, spLightColor, spLightDirection, 45.0f);
	Test_Model.Init("Assets/modelData/Car/f1.tkm");
	Test_Sprite.Init("Assets/Sprite/core2.dds", 1000.0f, 1000.0f);
}

void Test::Render(RenderContext& rc) {
	Test_Model.Draw(rc);
	//Test_Sprite.Draw(rc);
}