
#define __SHADER__
#include"TextureBase.hlsli"
#include"../../../ShaderHeaderFiles/HLSL/5.0/DrawPolygon.hlsli"


//ピクセルシェダ(PixelShader)//
//共用//
float4 main(VS_OUT _in) : SV_Target0
{
	float4 res = _in.color;
	res *= baseTex.Sample(baseSmp, _in.uv);

	//Out = BaseColor;

	clip(res.a < 0.01f ? -1 : 1);

	//float4 BackCol = BackBuffers.Sample(BackBufferSmp, In.Pos.xy);

	//Out = Out.a == 1.0f ? Out : float4(float3(Out.rgb * Out.a).rgb + float3(BackCol.rgb * (1.0f - Out.a)).rgb, 1);
	//

	return res;

}