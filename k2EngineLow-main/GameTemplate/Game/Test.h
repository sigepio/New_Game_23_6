#pragma once
class Test:public IGameObject
{
public:
	Test();
	
	void Render(RenderContext& rc);

	ModelRender Test_Model;
	SpriteRender Test_Sprite;
};

