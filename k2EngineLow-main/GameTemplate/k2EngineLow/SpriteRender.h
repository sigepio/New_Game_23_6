#pragma once
namespace nsK2EngineLow {
	class SpriteRender
	{
	public:
		//初期化
		void Init(const char* filePath,
			const float w,
			const float h,
			AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans);

		//座標設定
		void SetPosition(const Vector3& pos) {
			m_position = pos;
		}
		void SetPosition(float x, float y, float z) {
			SetPosition({ x,y,z });
		}
		void SetPosition(float xyz) {
			SetPosition({ xyz,xyz,xyz });
		}

		//座標取得
		const Vector3& GetPosition()const {
			return m_position;
		}

		//大きさを設定
		void SetScale(const Vector3& scale) {
			m_scale = scale;
		}
		void SetScale(float x, float y, float z) {
			SetScale({ x,y,z });
		}
		void SetScale(const float& scale) {
			m_scale.x = scale;
			m_scale.y = scale;
			m_scale.z = scale;
		}

		//大きさを取得
		const Vector3& GetScale()const
		{
			return m_scale;
		}

		//回転を設定
		void SetRotation(const Quaternion& rot) {
			m_rotation = rot;
		}

		//ピボットの設定
		void SetPivot(const Vector2& pivot) {
			m_pivot=pivot;
		}
		void SetPivot(float x, float y) {
			SetPivot({ x,y });
		}
		void SetPivot(float xy) {
			SetPivot({ xy,xy });
		}

		//ピボットを取得
		const Vector2& GetPivot()const
		{
			return m_pivot;
		}
		
		//乗算カラーを設定
		void SetMulColor(const Vector4& mulColor) {
			m_sprite.SetMulColor(mulColor);
		}
		void SetMUlColor(float x, float y, float z, float w) {
			SetMulColor({ x,y,z,w });
		}
		void SetMulColor(float xyz, float w) {
			SetMulColor({ xyz,xyz,xyz,w });
		}
		void SetMulColor(const Vector3& mulColor, float w) {
			SetMulColor(mulColor, w);
		}

		//乗算カラーを取得
		const Vector4& GetMulColor()const
		{
			return m_sprite.GetMulColor();
		}

		//更新処理
		void Update() {
			m_sprite.Update(m_position,
				m_rotation,
				m_scale,
				m_pivot);
		}

		//描画処理
		void Draw(RenderContext& rc);

		void OnDraw(RenderContext& rc)
		{
			m_sprite.Draw(rc);
		}

	private:
	public:
	private:
		Sprite m_sprite;
		Vector3 m_position = Vector3::Zero;
		Vector3 m_scale = Vector3::One;
		Quaternion m_rotation = Quaternion::Identity;
		Vector2 m_pivot = Sprite::DEFAULT_PIVOT;

	};
}

