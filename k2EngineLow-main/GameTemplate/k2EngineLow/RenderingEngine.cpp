#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {
	RenderingEngine* RenderingEngine::m_instance = nullptr;

	RenderingEngine::RenderingEngine() {
		

		//最終的なテクスチャを張り付けるためのスプライトを初期化
		/*InitFinalSprite();*/
	}

	bool RenderingEngine::Start()
	{
		return true;
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{
		

		// モデルの描画
		ModelDraw(rc);
		SpriteFontDraw(rc);

		// クリア
		ModelRenderObject.clear();
		
	}

	void RenderingEngine::Init() {

	}

	void RenderingEngine::ModelDraw(RenderContext& rc) {
		

		//まとめてモデルレンダーを描画
		for (auto MobjData : ModelRenderObject) {
			MobjData->OnDraw(rc);
		}
		
		/*rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);*/
	}
	void RenderingEngine::SpriteFontDraw(RenderContext& rc) {
		for (auto SobjData : SpriteRenderObject) {
			SobjData->OnDraw(rc);
		}
		for (auto FobjData : FontRenderObject) {
			FobjData->OnDraw(rc);
		}
	}
	void RenderingEngine::CopyMainRenderTargetToFrameBuffer(RenderContext& rc) {
		
	}
}