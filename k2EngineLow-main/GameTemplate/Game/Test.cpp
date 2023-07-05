#include "stdafx.h"
#include "Test.h"

Test::Test() {
	//���C�g�����̐��K��
	Light_Direction.Normalize();
	//�f�B���N�V�������C�g�̐ݒ�
	RenderingEngine::GetInstance()->SetDirectionLight(Light_Direction, Light_Color);

	RenderingEngine::GetInstance()->SetPointLight(0, {0.0f,50.0f,50.0f}, 100.0f, {15.0f,0.0f,0.0f});
	
	RenderingEngine::GetInstance()->SetSpotLight(0, { 0.0f,70.0f,0.0f }, 1000.0f, spLightColor, spLightDirection, 45.0f);
	Test_Model.Init("Assets/modelData/unityChan.tkm");
	Test_Sprite.Init("Assets/Sprite/core2.dds", 1000.0f, 1000.0f);
}

void Test::Render(RenderContext& rc) {
	Test_Model.Draw(rc);
	//Test_Sprite.Draw(rc);
}