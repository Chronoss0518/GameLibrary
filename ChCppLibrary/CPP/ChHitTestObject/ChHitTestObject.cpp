#include"../../BaseIncluder/ChBase.h"

#include"ChHitTestObject.h"
#include"ChHitTestRay.h"
#include"ChHitTestPanel.h"
#include"ChHitTestBox.h"
#include"ChHitTestSphere.h"
#include"ChHitTestMesh.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//HitTestRay Method//
///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestRay::IsHit(
	HitTestPanel* _target)
{
	auto square = _target->GetSquarePositions();

	ChStd::Bool hitFlg = HitTestTri(square.pos[0], square.pos[1], square.pos[2]);

	if (!hitFlg)hitFlg = HitTestTri(square.pos[0], square.pos[2], square.pos[3]);

	return hitFlg;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestRay::IsHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestRay::IsHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestRay::IsHit(
	HitTestMesh* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestRay::IsInnerHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestRay::IsInnerHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

float HitTestRay::CreateDat(const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3)
{

	ChMath::BaseMatrix3x3<float> mat;

	ChVec3 tmp[3] = { _vec1,_vec2,_vec3 };

	for (unsigned char i = 0; i < mat.m.GetColumn(); i++)
	{
		for (unsigned char j = 0; j < mat.m.GetRow(); j++)
		{
			mat.m[i][j] = tmp[j].val[i];
		}
	}

	return mat.m.GetDeterminant();
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestRay::HitTestTri(const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3)
{

	//eg1 = (v1 - v0), eg2 = (v2 - v0);
	//hitPos = spos + (dir * len)
	//hitPos = (eg1 * u) + (eg2 * v) + v0
	//spos + (dir * len) = (eg1 * u) + (eg2 * v) + v0
	//spos - v0 = (eg1 * u) + (eg2 * v) - (dir * len)

	//spos1 - v01 = eg11 * u + eg21 * v - dir1 * len
	//spos2 - v02 = eg12 * u + eg22 * v - dir2 * len
	//spos3 - v03 = eg13 * u + eg23 * v - dir3 * len
	//spos - v0 = v2sp

	//u = dat(v2sp,eg2,-dir)/dat(eg1.eg2.-dir)
	//v = dat(eg1,v2sp,-dir)/dat(eg1.eg2.-dir)
	//len = dat(eg1,eg2,v2sp)/dat(eg1.eg2.-dir)

	ChVec3 pos = GetPos();
	ChVec3 dir = GetMat().TransformCoord(rayDir);

	float u = 0.0f, v = 0.0f, len = 0.0f;

	ChVec3 eg1 = _vec2 - _vec1, eg2 = _vec3 - _vec1, v2sp = pos - _vec1;

	ChVec3 mdir = dir * -1;
	float divDat = 0.0f;


	divDat = CreateDat(eg1, eg2, mdir);

	if (divDat <= 0.0f)return false;

	u = CreateDat(v2sp, eg2, mdir);

	u = u / divDat;

	if (u < 0.0f || u > 1.0f)return false;

	v = CreateDat(eg1, v2sp, mdir);
	v = v / divDat;

	if (v < 0.0f || v > 1.0f)return false;

	float tmpVal = u + v;

	if (tmpVal < 0.0f || tmpVal > 1.0f)return false;

	len = CreateDat(eg1, eg2, v2sp);
	len = len / divDat;

	if (len < 0.0f || len > maxLen)return false;

	SetHitVector(dir * len);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////
//HitTestPanel Method//
///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestPanel::IsHit(
	HitTestPanel* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestPanel::IsHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestPanel::IsHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestPanel::IsHit(
	HitTestMesh* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestPanel::IsInnerHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestPanel::IsInnerHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

Square HitTestPanel::GetSquarePositions()
{
	Square out;

	ChVec3 tmpPos[4] = {
		ChVec3(-size.x / 2.0f,size.y / 2.0f,0.0f),
		ChVec3(size.x / 2.0f,size.y / 2.0f,0.0f),
		ChVec3(size.x / 2.0f,-size.y / 2.0f,0.0f),
		ChVec3(-size.x / 2.0f,-size.y / 2.0f,0.0f) };

	{
		auto tmpMat = GetMat();

		for (unsigned char i = 0; i < 4; i++)
		{
			out.pos[i] = tmpMat.Transform(tmpPos[i]);
		}

	}

	return out;

}
///////////////////////////////////////////////////////////////////////////////////////
//HitTestBox Method//
///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestBox::IsHit(
	HitTestPanel* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestBox::IsHit(
	HitTestBox* _target)
{


	//位置情報だけの当たり判定//

	ChVec3 tPos = _target->GetPos();
	ChVec3 mPos = GetPos();

	ChVec3 tmpVec = mPos - tPos;
	ChVec3 tSize = _target->GetSize();
	ChVec3 mSize = size;

	ChVec3 testVec = tmpVec;
	testVec.Abs();


	if (tSize.x + mSize.x < testVec.x)return false;
	if (tSize.y + mSize.y < testVec.y)return false;
	if (tSize.z + mSize.z < testVec.z)return false;

	ChVec3 moveSize = testVec - (tSize + mSize);

	tmpVec *= moveSize;

	SetHitVector(tmpVec);

	_target->SetHitVector(tmpVec * -1.0f);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestBox::IsHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestBox::IsHit(
	HitTestMesh* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestBox::IsInnerHit(
	HitTestBox* _target)
{

	//位置情報だけの当たり判定//

	ChVec3 tPos = _target->GetPos();
	ChVec3 mPos = GetPos();

	ChVec3 tSize = _target->GetSize();
	ChVec3 mSize = size;

	ChVec3 testVec = mPos - tPos;
	testVec.Abs();


	ChVec3 hitFlgs = 0.0f;

	{

		if (tSize.x < testVec.x + mSize.x)hitFlgs.x = testVec.x + mSize.x - tSize.x;
		if (tSize.y < testVec.y + mSize.y)hitFlgs.y = testVec.y + mSize.y - tSize.y;
		if (tSize.z < testVec.z + mSize.z)hitFlgs.z = testVec.z + mSize.z - tSize.z;


		if (hitFlgs.Len() <= 0.0f)return false;
	}

	SetHitVector(hitFlgs);

	_target->SetHitVector(hitFlgs * -1.0f);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestBox::IsInnerHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////
//HitTestSphere Method//
///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestSphere::IsHit(
	HitTestPanel* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestSphere::IsHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestSphere::IsHit(
	HitTestSphere* _target)
{
	//位置情報だけの当たり判定//

	ChVec3 tPos = _target->GetPos();

	ChVec3 mPos = GetPos();

	ChVec3 tmpVec = mPos - tPos;

	float tmpLen = tmpVec.Len();

	if (tmpLen >= (_target->GetLen() + len))return false;

	tmpVec.Normalize();

	float moveSize = tmpLen - len;

	moveSize = _target->GetLen() - moveSize;

	SetHitVector(tmpVec * moveSize);

	_target->SetHitVector(tmpVec * (-moveSize));

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestSphere::IsHit(
	HitTestMesh* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestSphere::IsInnerHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestSphere::IsInnerHit(
	HitTestSphere* _target)
{

	//位置情報だけの当たり判定//

	ChVec3 tPos = _target->GetPos();
	ChVec3 mPos = GetPos();


	ChVec3 tmpVec = mPos - tPos;

	float tmpLen = tmpVec.Len();

	if (tmpLen + len <= _target->GetLen())return false;

	tmpVec.Normalize();

	float moveSize = tmpLen + len;

	moveSize = moveSize - _target->GetLen();

	SetHitVector(tmpVec * -moveSize);

	_target->SetHitVector(tmpVec * (moveSize));

	return true;

}

///////////////////////////////////////////////////////////////////////////////////////
//HitTestMesh Method//
///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestMesh::IsHit(
	HitTestPanel* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool HitTestMesh::IsHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestMesh::IsHit(
	HitTestSphere* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestMesh::IsHit(
	HitTestMesh* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestMesh::IsInnerHit(
	HitTestBox* _target)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool  HitTestMesh::IsInnerHit(
	HitTestSphere* _target)
{
	return false;
}
