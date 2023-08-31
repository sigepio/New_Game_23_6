#pragma once
namespace nsK2EngineLow {
	struct ModelInitDataFR :public ModelInitData
	{
		ModelInitDataFR()
		{
			m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
	};

	class ModelRender
	{
	public:
		ModelRender();
		~ModelRender();
		void InitCommon(const char* tkmFiliPath, AnimationClip* animationClips);
		void InitSkyCubeModel(ModelInitData& initData);
		
		//初期化
		void Init(const char* filePath,
			bool m_shadowDrop = true,//影(trueが影あり)
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ);
		//アップデート
		void Update(bool m_syuzinkou = false);
		//描画処理
		void Draw(RenderContext& rc);

		//座標設定
		void SetPosition(const Vector3& pos) {
			m_position = pos;//引数に設定した座標データを代入
		}
		//引数にfloat型の変数3つを入力した際Vector3型に変換してSetPosition(Vector3)関数を呼び出す
		void SetPosition(float x, float y, float z) {
			SetPosition({ x,y,z });
		}
		//引数にfloat型の同じ変数を入力した際Vector3型に変換してSetPosition(Vector3)関数を呼び出す
		void SetPosition(float xyz) {
			SetPosition({ xyz,xyz,xyz });
		}

		//回転処理
		void SetRotation(const Quaternion& rotation) {
			m_rotation = rotation;//引数に設定したQuaternionデータを代入
		}
		
		//拡大設定
		void SetScale(const Vector3& scale) {
			m_scale = scale;//引数に設定したVector3データを代入
		}
		void SetScale(float x, float y, float z) {
			SetScale({ x,y,z });
		}
		void SetScale(float xyz) {
			SetScale({ xyz,xyz,xyz });
		}

		//座標拡大回転すべてを設定
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3 scale) {
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
		}

		//モデルを取得
		Model& GetModel() {
			return m_model;
		}

		//モデルの座標を取得
		Vector3& GetPosition() {
			return m_position;
		}

		//モデルのX座標を取得
		float& GetPositionX() {
			return m_position.x;
		}
		//モデルのY座標を取得
		float& GetPositionY() {
			return m_position.y;
		}
		//モデルのZ座標を取得
		float& GetPositionZ() {
			return m_position.z;
		}

		bool& GetSyuzinkou() {
			return syuok;
		}

		//アニメーションの再生
		void PlayAnimation(int animNo, float interpolateTime = 0.0f) {//アニメーションクリップの番号、アニメーションの切り替えを滑らかにする時間
			Now_Animation_Number = animNo;//引数のアニメーションナンバーを代入
			m_animation.Play(animNo, interpolateTime);
		}

		//アニメーションクリップのナンバーを取得
		int GetAnimNum() {
			return Now_Animation_Number;
		}

		void OnDraw(RenderContext& rc) {
			m_model.Draw(rc,1);
		}

		void OnShadowDraw(RenderContext& rc)
		{
			m_shadowModel.Draw(rc, RenderingEngine::GetInstance()->GetLightCamera());
		}

		void PlayFlash() {
			m_flashFlag = true;
		}
		private:
			//アニメーションの初期化
			void InitAnimation(AnimationClip* animationClips,	//アニメーションクリップ
				int numAnimationClips,							//アニメーションクリップの数
				EnModelUpAxis enModelUpAxis);					//モデルの上向き

			//スケルトンの初期化
			void InitSkeleton(const char* filePath);
		public:

		private:
			//モデル
			Model m_model;
			Model m_shadowModel;
			Model m_zprepassModel;		//ZPrepassで描画されるモデル

			//アニメーション
			Animation m_animation;
			AnimationClip* m_animationClips;
			int m_numAnimationClips = 0;
			Skeleton m_skeleton;
			float m_animationSpeed = 1.0f;

			//座標・回転・大きさ
			Vector3 m_position = Vector3::Zero;
			Quaternion m_rotation = { 0.0f,0.0f,0.0f,1.0f };
			Vector3 m_scale = Vector3::One;

			bool syuok = false;
			bool m_flashFlag = false;

			int Now_Animation_Number = -1;
	};

}



