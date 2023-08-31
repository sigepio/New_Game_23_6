#pragma once
namespace nsK2EngineLow {
	class Depth_of_Field
	{
	public:
		Depth_of_Field();
		~Depth_of_Field();
		void Init(RenderTarget& renderTaeget);
		void Update();
		void Render(RenderContext& rc, RenderTarget& renderTarget);

	private:
		Model model;

		RenderTarget* mainRenderingTarget;
		RenderTarget depthRenderTarget;

		GaussianBlur blur;
		SpriteInitData combineBokeImageSpriteInitData;

		Sprite combineBokeImageSprite;
	};
}

