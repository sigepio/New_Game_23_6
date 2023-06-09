#include "k2EngineLowPreCompile.h"
#include "FontRender.h"
namespace nsK2EngineLow {
	void FontRender::Draw(RenderContext& rc)
	{
		RenderingEngine::GetInstance()->AddFontRenderObject(this);
	}
}