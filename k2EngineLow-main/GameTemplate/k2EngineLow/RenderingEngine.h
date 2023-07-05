#pragma once
#include "SceneLight.h"

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

		//ディレクションライトの設定
		void SetDirectionLight(Vector3 direction, Vector3 color)
		{
			m_sceneLight.SetDirectionLight(direction, color);
		}

		//ポイントライトの設定
		void SetPointLight(int num, Vector3 position, float range, Vector3 color)
		{
			m_sceneLight.SetPointLight(num, position, range, color);
		}
		//スポットライトの設定
		void SetSpotLight(int num, Vector3 position, float range, Vector3 color, Vector3 direction, float angle)
		{
			m_sceneLight.SetSpotLight(num, position, range, color, direction, angle);
		}

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
		SceneLight& GetLightingCB()
		{
			return m_sceneLight;
		}

		Light& GetLightCB()
		{
			return m_sceneLight.GetLight();
		}

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
		SceneLight m_sceneLight;

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

