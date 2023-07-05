/*!
 * @brief	シンプルなモデルシェーダー。
 */

////////////////////////////////////////////////
// ライト構造体
////////////////////////////////////////////////
struct DirectionLight
{
    float3 dirDirection;	//ディレクションライトの方向
    float3 dirColor;		//ディレクションライトのカラー
};
struct PointLight
{
    float3 ptPosition;	//ポイントライトの位置
    float3 ptColor;		//ポイントライトのカラー
    float  ptRange;		//ポイントライトの影響範囲
};
struct SpotLight
{
    float3 spPosition;		//スポットライトの位置
    float3 spColor;			//スポットライトのカラー
	float  spRange;			//スポットライトの射出範囲
    float3 spDirection;		//スポットライトの射出方向
    float  spAngle;			//スポットライトの射出角度
};
struct HemLight
{
    float3 heGroundColor;	//照り返しのライト
    float3 heSkyColor;		//天球ライト
    float3 heGroundNormal;	//地面の法線
};
////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};
cbuffer DirectionLightCb : register(b1) {
	//ディレクションライト用
    DirectionLight directionLight;

	float3 eyePos;
	float3 ambientLight;	//アンビエントライトの強さ
	
	//ポイントライト用
    PointLight pointLight[10];
	
	//スポットライト用
    SpotLight spotLight[10];
	
	//半球ライト用
    HemLight hemLight;
        
    //ライトビュースクリーン用
    float4x4 mLVP;
    
    bool setGrayScale;
	
}
////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos			: POSITION;		//モデルの頂点座標。
    float2 uv			: TEXCOORD0;	//UV座標。
    float3 tangent		: TANGENT;		
    float3 biNormal		: BINORMAL;
	float3 normal		: NORMAL;		//法線
	SSkinVSIn skinVert;					//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float2 uv 			: TEXCOORD0;	//uv座標。
	float3 worldPos		: TEXCOORD1;	//ワールド座標
	float3 normal		: NORMAL;		//法線
    float3 tangent		: TANGENT;		//接ベクトル
    float3 biNormal		: BINORMAL;		//従ベクトル
    float3 normalInView : TEXCOORD2;	//カメラ空間の法線
    float4 posInProj    : TEXCOORD3;    //輪郭線の為の変数
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
Texture2D<float4> g_normalMap : register(t1);			//法線マップにアクセスするための変数を追加
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
Texture2D<float4> g_specularMap : register(t2);         //スペキュラーマップにアクセスするための変数を追加
Texture2D<float4> g_depthTexture : register(t10);       //深度
Texture2D<float4> g_shadowMap : register(t11);          //シャドウマップ
sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);
float3 CalcLigFromPointLight(SPSIn psIn, int num);
float3 CalcLigFromSpotLight(SPSIn psIn, int num);
/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;
	float4x4 m;
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}
	psIn.pos = mul(m, vsIn.pos);
	psIn.worldPos = psIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

	//頂点法線をピクセルシェーダーに渡す
	//psIn.normal=normalize(mul(m,vsIn.normal));
	//接ベクトルと従ベクトルをワールド空間に変換する
	//psIn.tangent=normalize(mul(m,vsIn.tangent));
	//psIn.biNormal=normalize(mul(m,vsIn.biNormal));

	psIn.normal=mul(mWorld,vsIn.normal);
	psIn.uv = vsIn.uv;


	//psIn.posInProj=psIn.pos;

	return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain( SPSIn psIn ) : SV_Target0
{
	float3 diffuseLig = CalcLambertDiffuse(directionLight.dirDirection, directionLight.dirColor, psIn.normal);
	float3 specDirection=CalcPhongSpecular(directionLight.dirDirection, directionLight.dirColor, psIn.worldPos, psIn.normal);
	float3 lig =diffuseLig+specDirection;

	//複数個のライティング計算
    float3 pointLig[10];
    float3 spotLig[10];
    for (int i = 0; i < 10; i++)
    {
        //ポイントライト(鏡面拡散どっちも)によるライティングを計算
        pointLig[i] = CalcLigFromPointLight(psIn, i);
		//スポットライト(鏡面拡散どっちも)によるライティングを計算
        spotLig[i] = CalcLigFromSpotLight(psIn, i);
        
    }


	for (int i = 0; i < 10; i++)
    {
        lig += pointLig[i];
		lig += spotLig[i];
        
    }
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);
	albedoColor.xyz*=lig;
	return albedoColor;
}


//Lambert拡散反射光を計算する
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
	// ピクセルの法線とライトの方向の内積を計算する
	float t = dot(normal, lightDirection) * -1.0f;
	// 内積の値を0以上の値にする
	if (t < 0.0f)
	{
		t = 0.0f;
	}

	// 拡散反射光を計算する
	return lightColor * t;
}

//Phong鏡面反射光を計算する
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
	// 反射ベクトルを求める
	float3 refVec = reflect(lightDirection, normal);

	// 光が当たったサーフェイスから視点に伸びるベクトルを求める
	float3 toEye = eyePos - worldPos;
	toEye = normalize(toEye);

	// 鏡面反射の強さを求める
	float t = dot(refVec, toEye);
	// 鏡面反射の強さを0以上の数値にする
	if (t < 0.0f)
	{
		t = 0.0f;
	}

	// 鏡面反射の強さを絞る
	t = pow(t, 5.0f);

	// 鏡面反射光を求める
    return lightColor * t;
}
float3 CalcLigFromPointLight(SPSIn psIn, int num)
{
	// このサーフェイスに入射しているポイントライトの光の向きを計算する
    float3 ligDir = psIn.worldPos - pointLight[num].ptPosition;

    // 正規化して大きさ1のベクトルにする
    ligDir = normalize(ligDir);

    // 減衰なしのLambert拡散反射光を計算する
    float3 diffPoint = CalcLambertDiffuse(
        ligDir, // ライトの方向
        pointLight[num].ptColor, // ライトのカラー
        psIn.normal			// サーフェイスの法線
    );

    // 減衰なしのPhong鏡面反射光を計算する
    float3 specPoint = CalcPhongSpecular(
        ligDir, // ライトの方向
       pointLight[num].ptColor, // ライトのカラー
        psIn.worldPos, // サーフェイズのワールド座標
        psIn.normal			// サーフェイズの法線
    );

    // 距離による影響率を計算する
    // ポイントライトとの距離を計算する
    float3 distance = length(psIn.worldPos - pointLight[num].ptPosition);

    // 影響率は距離に比例して小さくなっていく
    float affect = 1.0f - 1.0f / pointLight[num].ptRange * distance;
    // 影響力がマイナスにならないように補正をかける
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }

    // 影響の仕方を指数関数的にする。今回のサンプルでは3乗している
    affect = pow(affect, 3.0f);

    // 拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
    diffPoint *= affect;
    specPoint *= affect;

    return diffPoint + specPoint;
}

//スポットライトによる反射光を計算する
float3 CalcLigFromSpotLight(SPSIn psIn, int num)
{
	//サーフェイスに入射するスポットライトの光の向きを計算する
    float3 LigDir = psIn.worldPos - spotLight[num].spPosition;
	//正規化
    LigDir = normalize(LigDir);
	//減衰なしのLambert拡散反射光を計算する
    float3 diffSpot = CalcLambertDiffuse(
		LigDir, //スポットライトの方向
		spotLight[num].spColor, //スポットライトのカラー
		psIn.normal			//サーフェイスの法線
	);
	//減衰なしのPhong鏡面反射の計算
    float3 specSpot = CalcPhongSpecular(
		LigDir, //ライトの方向
		spotLight[num].spColor, //ライトのカラー
		psIn.worldPos, //サーフェイスのワールド座標
		psIn.normal			//サーフェイスの法線
	);
	//スポットライトとの距離を計算する
    float distance = length(psIn.worldPos - spotLight[num].spPosition);
	//影響率は距離に比例して小さくなっていく
    float affect = 1.0f - 1.0f / spotLight[num].spRange * distance;
	//影響力がマイナスにならないように
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
	//影響を指数関数的にする
    affect = pow(affect, 3.0f);
	//拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
    diffSpot *= affect;
    specSpot *= affect;
	//入射光と射出方向の角度を求める
    float angle = dot(LigDir, spotLight[num].spDirection);
	//dot()で求めた値をacos()に渡して角度を求める
    angle = abs(acos(angle));
	//角度に比例して小さくなっていく影響率を計算する
    affect = 1.0f - 1.0f / spotLight[num].spAngle * angle;
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
	//影響を指数関数的にする
    affect = pow(affect, 0.5f);
	//角度による影響率を反射光に乗算して、影響を弱める
    diffSpot *= affect;
    specSpot *= affect;
	
    return diffSpot + specSpot;
}