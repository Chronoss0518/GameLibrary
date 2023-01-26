#ifndef _HLSL_Shader_Public_
#define _HLSL_Shader_Public_

#ifndef CHANGE_CBUFFER_5
#define CHANGE_CBUFFER_5(_no) b##_no
#endif
#ifndef CHANGE_TBUFFER_5
#define CHANGE_TBUFFER_5(_no) t##_no
#endif
#ifndef CHANGE_SBUFFER_5
#define CHANGE_SBUFFER_5(_no) s##_no
#endif

#ifndef __SHADER__
#ifndef SHADER_TO_CPP
#define SHADER_TO_CPP

#ifndef row_major
#define row_major
#endif

#ifndef uniform
#define uniform
#endif

#ifndef column_major
#define column_major
#endif

using uint4x4 = ChMath::BaseMatrix4x4<unsigned int>;
using uint3 = ChMath::Vector3Base<unsigned int>;
using uint2 = ChMath::Vector2Base<unsigned int>;
using uint = unsigned int;
using float4x4 = ChLMat;
using float3x3 = ChLMat;
using float2x2 = ChLMat;
using float4 = ChVec4;
using float3 = ChVec3;
using float2 = ChVec2;

#endif
#endif

#endif