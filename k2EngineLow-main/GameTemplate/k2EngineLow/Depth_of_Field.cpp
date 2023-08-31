#include "k2EngineLowPreCompile.h"
#include "Depth_of_Field.h"
namespace nsK2EngineLow {
	Depth_of_Field::Depth_of_Field() 
	{

	}

	Depth_of_Field::~Depth_of_Field()
	{

	}

	void Depth_of_Field::Init(RenderTarget& renderTarget) 
	{
		Light light;
		depthRenderTarget.Create(
			1280,
			720,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN
		);

		blur.Init(&mainRenderingTarget->GetRenderTargetTexture());

		combineBokeImageSpriteInitData.m_textures[0] = &blur.GetBokeTexture();
		combineBokeImageSpriteInitData.m_textures[1] = &depthRenderTarget.GetRenderTargetTexture();
		combineBokeImageSpriteInitData.m_width = 1280;
		combineBokeImageSpriteInitData.m_height = 720;

		combineBokeImageSpriteInitData.m_fxFilePath= "Assets/shader/PostEffect.fx";
		combineBokeImageSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		combineBokeImageSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Trans;

		combineBokeImageSprite.Init(combineBokeImageSpriteInitData);

		InitModel(model, light);
	}

	void Depth_of_Field::Render(RenderContext& rc, RenderTarget& renderTarget)
	{
		g_engine->BeginFrame();

		RenderTarget* rts[] = {
			&mainRenderingTarget,
			&depthRenderTarget
		};

		rc.WaitUntilToPossibleSetRenderTargets(2, rts);
		rc.SetRenderTargetsAndViewport(2, rts);
		rc.ClearRenderTargetViews(2, rts);


		rc.WaitUntilFinishDrawingToRenderTargets(2, rts);

		blur.ExecuteOnGPU(rc, 5);


	}
}