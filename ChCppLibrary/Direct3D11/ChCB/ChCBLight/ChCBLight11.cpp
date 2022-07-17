#include<Windows.h>
#include"../../../BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"ChCBLight11.h"

using namespace ChD3D11;
using namespace CB;

///////////////////////////////////////////////////////////////////////////////////
//LightHeader Method
///////////////////////////////////////////////////////////////////////////////////

void Light11::Init(ID3D11Device* _device)
{
	Release();

	device = _device;

	buf.CreateBuffer(_device, LIGHT_DATA_REGISTERNO);
	{
		ChVec4 tmpCol[256];

		for (unsigned long i = 0; i < 256; i++)
		{
			tmpCol[i] = ChVec4(i / 256.0f, i / 256.0f, i / 256.0f, 1.0f);
		}

		lightPow.CreateColorTexture(device, tmpCol, 256, 1);


		D3D11_SAMPLER_DESC samp;

		samp.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samp.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samp.Filter = D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;

		lightPow.SetSampler(samp);
	}



	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::Release()
{
	if (!*this)return;

	buf.Release();

	lightPow.Release();

	SetInitFlg(false);
}

void Light11::SetLightDiffuse(const ChVec3& _dif)
{
	if (!*this)return;

	lightDatas.light.dif = _dif;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::SetUseLightFlg(const bool& _flg)
{
	if (!*this)return;

	lightDatas.light.useFlg = _flg;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::SetLightDir(const ChVec3& _dir)
{
	if (!*this)return;

	lightDatas.light.dir = _dir;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::SetLightAmbientPow(const float _amb)
{
	if (!*this)return;

	lightDatas.light.ambPow = _amb;

	updateFlg = true;
}

void Light11::SetDirectionLightData(const bool _useFlg, const ChVec3& _dif, const ChVec3& _dir, const float _ambPow)
{

	lightDatas.light.useFlg = _useFlg;
	lightDatas.light.dif = _dif;
	lightDatas.light.dir = _dir;
	lightDatas.light.ambPow = _ambPow;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::SetPLightPos(const ChVec3& _pos, const unsigned long _no)
{
	if (!*this)return;
	if (_no > LIGHT_PLIGHTCOUNT)return;

	lightDatas.pLight[_no].pos = _pos;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::SetPLightLen(const float _len, const unsigned long _no)
{
	if (!*this)return;
	if (_no > LIGHT_PLIGHTCOUNT)return;

	lightDatas.pLight[_no].len = _len;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::SetPLightDiffuse(const ChVec3& _dif, const unsigned long _no)
{
	if (!*this)return;
	if (_no > LIGHT_PLIGHTCOUNT)return;

	lightDatas.pLight[_no].dif = _dif;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::SetPLightUseFlg(const bool& _flg, const unsigned long _no)
{
	if (!*this)return;
	if (_no > LIGHT_PLIGHTCOUNT)return;

	lightDatas.pLight[_no].useFlg = _flg;

	updateFlg = true;
}

void Light11::SetPointLightData(const bool _useFlg, const ChVec3& _dif, const ChVec3& _pos, const float _len, const unsigned long _no)
{

	if (!*this)return;
	if (_no > LIGHT_PLIGHTCOUNT)return;

	lightDatas.pLight[_no].useFlg = _useFlg;
	lightDatas.pLight[_no].dif = _dif;
	lightDatas.pLight[_no].pos = _pos;
	lightDatas.pLight[_no].len = _len;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::SetCamPos(const ChVec3& _camPos)
{
	if (!*this)return;

	lightDatas.camPos = _camPos;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::SetLightData(const ChLightData& _ld)
{
	if (!*this)return;

	lightDatas.camPos = _ld.camPos;
	lightDatas.light = _ld.light;
	for (unsigned long i = 0; i < 10; i++)
	{
		lightDatas.pLight[i] = _ld.pLight[i];
	}

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::SetPSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	Update(_dc);

	buf.SetToPixelShader(_dc);

	SetTexture(_dc);
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::SetVSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	Update(_dc);

	buf.SetToVertexShader(_dc);

	SetTexture(_dc);
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::SetDrawData(ID3D11DeviceContext* _dc)
{

	if (!*this)return;

	Update(_dc);

	buf.SetToVertexShader(_dc);
	buf.SetToPixelShader(_dc);


	SetTexture(_dc);
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::SetImportLightPowMap(ChPtr::Shared<TextureBase11>& _lightPowMap)
{
	if (!*this)return;

	importLightPowMap = _lightPowMap;
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::ClearImportLightPowMap()
{
	if (!*this)return;

	importLightPowMap.reset();
}

void Light11::SetTexture(ID3D11DeviceContext* _dc)
{

	TextureBase11* tmpLightPow = &lightPow;

	if (!importLightPowMap.expired())
	{
		if (importLightPowMap.lock()->IsTex())
		{
			tmpLightPow = importLightPowMap.lock().get();
		}
	}

	tmpLightPow->SetDrawData(_dc, LIGHT_TEXTURE_REGISTERNO);
}

///////////////////////////////////////////////////////////////////////////////////

void Light11::Update(ID3D11DeviceContext* _dc)
{
	if (!updateFlg)return;

	buf.UpdateResouce(_dc, &lightDatas);
}