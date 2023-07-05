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

		//�f�B���N�V�������C�g�̐ݒ�
		void SetDirectionLight(Vector3 direction, Vector3 color)
		{
			m_sceneLight.SetDirectionLight(direction, color);
		}

		//�|�C���g���C�g�̐ݒ�
		void SetPointLight(int num, Vector3 position, float range, Vector3 color)
		{
			m_sceneLight.SetPointLight(num, position, range, color);
		}
		//�X�|�b�g���C�g�̐ݒ�
		void SetSpotLight(int num, Vector3 position, float range, Vector3 color, Vector3 direction, float angle)
		{
			m_sceneLight.SetSpotLight(num, position, range, color, direction, angle);
		}

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
		/// �C���X�^���X���擾�B
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

