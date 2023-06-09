#pragma once

namespace nsK2EngineLow {

	class ModelRender;
	class SpriteRender;
	class FontRender;

	class RenderingEngine:public Noncopyable
	{
	public:
		RenderingEngine();
		bool Start();
		/*void InitShadowMap();
		void InitZPrepassRenderTarget();
		void InitFinalSprite();
		void InitToonMap();
		void Init2DSprite();*/
		void Execute(RenderContext& rc);
		/*void ZPrepass(RenderContext& rc);
		void ShadowDraw(RenderContext& rc);*/
		void ModelDraw(RenderContext& rc);
		void SpriteFontDraw(RenderContext& rc);
		void Init();
		void CopyMainRenderTargetToFrameBuffer(RenderContext& rc);


		void AddModelRenderObject(ModelRender* modelRender)
		{
			//�R���e�i�̌��ɂ�������
			ModelRenderObject.push_back(modelRender);
		}
		void AddSpriteRenderObject(SpriteRender* spriteRender)
		{
			//�R���e�i�̌��ɂ�������
			SpriteRenderObject.push_back(spriteRender);
		}
		void AddFontRenderObject(FontRender* fontRender)
		{
			//�R���e�i�̌��ɂ�������
			FontRenderObject.push_back(fontRender);
		}


		//�擾�n�̊֐�
		/*RenderTarget& GetMainRenderTarget()
		{
			return m_mainRenderTarget;
		}*/

		static void CreateInstance()
		{
			m_instance = new RenderingEngine;
			m_instance->Init();
		}
		static void DeleteInstance()
		{
			delete m_instance;
		}
		/// <summary>
		/// �C���X�^���X���擾�B
		/// </summary>
		/// <returns></returns>
		static RenderingEngine* GetInstance()
		{
			return m_instance;
		}
	private:
		/*RenderTarget m_mainRenderTarget;*/

		/*Sprite		 m_mainSprite;*/
		/*SpriteInitData m_spriteInitData;*/
		/*Sprite m_copyToframeBufferSprite;*/
		static RenderingEngine* m_instance;

		std::vector<ModelRender*>ModelRenderObject;
		std::vector<SpriteRender*>SpriteRenderObject;
		std::vector<FontRender*>FontRenderObject;
	};
}

