#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {
	RenderingEngine* RenderingEngine::m_instance = nullptr;

	RenderingEngine::RenderingEngine() {
		

		//�ŏI�I�ȃe�N�X�`���𒣂�t���邽�߂̃X�v���C�g��������
		/*InitFinalSprite();*/
	}

	bool RenderingEngine::Start()
	{
		return true;
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{
		

		// ���f���̕`��
		ModelDraw(rc);
		SpriteFontDraw(rc);

		// �N���A
		ModelRenderObject.clear();
		
	}

	void RenderingEngine::Init() {

	}

	void RenderingEngine::ModelDraw(RenderContext& rc) {
		

		//�܂Ƃ߂ă��f�������_�[��`��
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