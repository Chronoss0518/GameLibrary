#ifdef _WINDOWS_

#ifndef Ch_D3D9_Inc_h
#define Ch_D3D9_Inc_h

#ifndef CRT
#define CRT
#endif

///////////////////////////////////////////////////////////////////////////////////////
//DirectX関連
///////////////////////////////////////////////////////////////////////////////////////

#include"BaseIncluder/ChD3D9I.h"

///////////////////////////////////////////////////////////////////////////////////////
//D3D9AddStruct
///////////////////////////////////////////////////////////////////////////////////////

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib, "dsound.lib")

struct PNTVertex
{
	ChVector3_9 Pos;
	ChVector3_9 Normal;
	D3DXVECTOR2 Tex;
};

//C/C++言語簡略型関数クラス//

//System操作//
#include"Direct3D9/ChDSound/ChDSound9.h"
//Object本体//
#include"Direct3D9/ChMesh/ChBaseMesh9.h"
#include"Direct3D9/ChTexture/ChBaseTexture9.h"
//空間操作//
#include"Direct3D9/ChCameraController/ChCameraController9.h"
#include"Direct3D9/ChLight/ChLight9.h"
#include"Direct3D9/ChRenderTargetManager/ChRenderTargetManager9.h"
#include"Direct3D9/ChRenderTargetList/ChRenderTargetList9.h"
//Object操作//
#include"Direct3D9/ChAnimationObject/ChAnimationObject9.h"
#include"Direct3D9/ChTextureList/ChTextureList9.h"
#include"Direct3D9/ChTexManager/ChTexManager9.h"
#include"Direct3D9/ChMeshManager/ChMeshManager9.h"
#include"Direct3D9/ChMeshList/ChMeshList9.h"
#include"Direct3D9/ChSprite/ChSprite9.h"
#include"Direct3D9/ChPolygonBoard/ChPolygonBoard9.h"
#include"Direct3D9/ChObjectController/ChObjectController9.h"
#include"Direct3D9/ChShader/ChShader9.h"
#include"Direct3D9/ChStringController/ChStringController9.h"
#include"Direct3D9/ChFont/ChFont9.h"
#include"Direct3D9/ChPhysicalBase/ChPhysicalBase9.h"
#include"Direct3D9/ChBoundingBox/ChBoundingBox9.h"
#include"Direct3D9/ChMesh/ChSkinMesh9.h"
//Component//
#include"Direct3D9/ChComponent/ChComponent9.h"
#include"Direct3D9/ChComponent/ChTextureComponent9.h"
#include"Direct3D9/ChComponent/ChModelComponents9.h"

#ifdef _DEBUG

#ifdef _DLL
#pragma comment(lib,"ChD3D9Library_MDd.lib")
#else
#pragma comment(lib,"ChD3D9Library_MTd.lib")
#endif

#else

#ifdef _DLL
#pragma comment(lib,"ChD3D9Library_MD.lib")
#else
#pragma comment(lib,"ChD3D9Library_MT.lib")
#endif

#endif

//CopyRight Chronoss0518 2018/08//
#endif

#endif