#include "stdafx.h"
#include "Test.h"

Test::Test() {
	Test_Model.Init("Assets/modelData/unityChan.tkm");
	Test_Sprite.Init("Assets/Sprite/core2.dds", 1000.0f, 1000.0f);
}

void Test::Render(RenderContext& rc) {
	Test_Model.Draw(rc);
	Test_Sprite.Draw(rc);
}