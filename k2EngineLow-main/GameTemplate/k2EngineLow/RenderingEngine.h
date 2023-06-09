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
			//コンテナの後ろにくっつける
			ModelRenderObject.push_back(modelRender);
		}
		void AddSpriteRenderObject(SpriteRender* spriteRender)
		{
			//コンテナの後ろにくっつける
			SpriteRenderObject.push_back(spriteRender);
		}
		void AddFontRenderObject(FontRender* fontRender)
		{
			//コンテナの後ろにくっつける
			FontRenderObject.push_back(fontRender);
		}


		//取得系の関数
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
		/// インスタンスを取得。
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

