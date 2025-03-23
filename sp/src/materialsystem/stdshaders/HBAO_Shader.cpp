#include "BaseVSShader.h"
#include "hbao_vs30.inc"
#include "hbao_ps30.inc"

BEGIN_VS_SHADER(HBAO, "Horizon-Based Ambient Occlusion")
BEGIN_SHADER_PARAMS
SHADER_PARAM(DEPTHTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_Depth", "Depth buffer texture")
SHADER_PARAM(RADIUS, SHADER_PARAM_TYPE_FLOAT, "0.5", "AO radius")
SHADER_PARAM(BIAS, SHADER_PARAM_TYPE_FLOAT, "0.1", "Depth bias")
SHADER_PARAM(INTENSITY, SHADER_PARAM_TYPE_FLOAT, "1.0", "AO intensity")
END_SHADER_PARAMS

SHADER_INIT
{
    LoadTexture(DEPTHTEXTURE);
}

SHADER_FALLBACK
{
    return 0;
}

SHADER_DRAW
{
    SHADOW_STATE
    {
        pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);
        pShaderShadow->VertexShaderVertexFormat(VERTEX_POSITION, 1, 0, 0);
        pShaderShadow->SetVertexShader("hbao_vs30", 0);
        pShaderShadow->SetPixelShader("hbao_ps30", 0);
    }
    DYNAMIC_STATE
    {
        BindTexture(SHADER_SAMPLER0, DEPTHTEXTURE, -1);
        SetVertexShaderConstant(0, params[RADIUS]->GetFloatValue());
        SetPixelShaderConstant(0, params[BIAS]->GetFloatValue());
        SetPixelShaderConstant(1, params[INTENSITY]->GetFloatValue());
    }
    Draw();
}
END_SHADER
