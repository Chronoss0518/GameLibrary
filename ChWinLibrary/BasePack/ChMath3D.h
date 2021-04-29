#ifndef Ch_CPP_Math3D_h
#define Ch_CPP_Math3D_h

#include <float.h>
#include <cmath>

#include"ChMath.h"

struct D3DXVECTOR4;
struct D3DXVECTOR3;
struct D3DXVECTOR2;

struct D3DXMATRIX;
struct D3DXQUATERNION;

namespace DirectX
{
	struct XMFLOAT3;
	struct XMFLOAT4;
	struct XMFLOAT4X4;
} // namespace DirectX

struct ChVector4;
struct ChVector3;
struct ChVector2;
struct ChRMatrix;
struct ChLMatrix;
struct ChUIMatrix;

namespace ChMath
{


	template<typename T>
	struct ChVector4Base
	{

		union {
			struct
			{
				T x, y, z, w;
			};
			struct
			{
				T r, g, b, a;
			};
			struct
			{
				T left, top, right, down;
			};
			VectorBase<T, 4> val;
		};
	};

	template<typename T>
	struct ChVector3Base
	{

		union {
			struct
			{
				T x, y, z;
			};
			struct
			{
				T r, g, b;
			};
			VectorBase<T, 3> val;
		};
	};

	template<typename T>
	struct ChVector2Base
	{

		union {
			struct
			{
				T x, y;
			};
			struct
			{
				T w, h;
			};
			VectorBase<T, 2> val;
		};
	};

	struct ChQuaternionBase
	{

		union {
			struct
			{
				float x, y, z, w;
			};
			float val[4]{ 0, 0, 0, 0 };
		};
	};

	template<typename T>
	struct ChBaseMatrix2x2
	{
		union
		{
			struct
			{

				T l_11, l_12;
				T l_21, l_22;

			};
			struct
			{

				T r_11, r_21;
				T r_12, r_22;

			};
			T m[2][2];
		};

	};

	template<typename T>
	struct ChBaseMatrix3x3
	{


		union
		{
			struct
			{

				T l_11, l_12, l_13;
				T l_21, l_22, l_23;
				T l_31, l_32, l_33;

			};
			struct
			{

				T r_11, r_21, r_31;
				T r_12, r_22, r_32;
				T r_13, r_23, r_33;

			};
			MatrixBase<T, 3, 3> m;
		};

	};

	template<typename T>
	struct ChBaseMatrix4x4
	{
		union
		{
			struct
			{

				T l_11, l_12, l_13, l_14;
				T l_21, l_22, l_23, l_24;
				T l_31, l_32, l_33, l_34;
				T l_41, l_42, l_43, l_44;

			};
			struct
			{

				T r_11, r_21, r_31, r_41;
				T r_12, r_22, r_32, r_42;
				T r_13, r_23, r_33, r_43;
				T r_14, r_24, r_34, r_44;

			};
			MatrixBase<T, 4, 4> m;
		};

	};

} // namespace ChMath

struct ChVector4 : public ChMath::ChVector4Base<float>
{

	///////////////////////////////////////////////////////////////////////////////////
	//StaticFunction//


	///////////////////////////////////////////////////////////////////////////////////
	//Operator//

	ChVector4& operator*=(const float& _num);
	ChVector4 operator*(const float& _num) const;
	ChVector4& operator/=(const float& _num);
	ChVector4 operator/(const float& _num) const;
	ChVector4& operator=(const float& _num);

	ChVector4& operator=(const ChVector4& _vec);
	ChVector4& operator-=(const ChVector4& _vec);
	ChVector4 operator-(const ChVector4& _vec) const;
	ChVector4& operator+=(const ChVector4& _vec);
	ChVector4 operator+(const ChVector4& _vec) const;
	ChVector4& operator*=(const ChVector4& _vec);
	ChVector4 operator*(const ChVector4& _vec) const;
	ChVector4& operator/=(const ChVector4& _vec);
	ChVector4 operator/(const ChVector4& _vec) const;

	bool operator==(const ChVector4& _vec)const
	{
		return (x == _vec.x && y == _vec.y && z == _vec.z && w == _vec.w);
	}

	bool operator!=(const ChVector4& _vec)const
	{
		return (x != _vec.x || y != _vec.y || z != _vec.z || w != _vec.w);
	}

	operator const ChVector3() const;
	operator const ChVector2() const;

	operator const D3DXVECTOR4() const;
	operator const D3DXVECTOR4* () const;

	ChVector4& operator=(const D3DXVECTOR4&);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChVector4()
	{
		val.Identity();
	}

	inline ChVector4(const float _num)
	{

		val.Set(_num);

		if (w < -1.0f)
			w = -1.0f;
		if (w > 1.0f)
			w = 1.0f;
	}

	inline ChVector4(
		const float _x, const float _y, const float _z, const float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		if (w < -1.0f)
			w = -1.0f;
		if (w > 1.0f)
			w = 1.0f;
	}

	inline ChVector4(const ChVector4& _vec) { *this = _vec; }

	inline ChVector4(const D3DXVECTOR4& _vec) { *this = _vec; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	std::string SerializeARGB(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6);

	void DeserializeARGB(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	static ChVector4 GetCross(
		const ChVector4& _vec1, const ChVector4& _vec2);

	static float GetCos(
		const ChVector4& _vec1, const ChVector4& _vec2);

	static float GetRadian(
		const ChVector4& _vec1, const ChVector4& _vec2);

	static float GetDot(
		const ChVector4& _vec1, const ChVector4& _vec2);

	//補正を行う(Nowは0〜1)
	static ChVector4 GetCorrection(
		const ChVector4& _start, const ChVector4& _end, const float _Now);

	static float GetLen(
		const ChVector4& _vec1, const ChVector4& _vec2);

	///////////////////////////////////////////////////////////////////////////////////

	inline float Len() const
	{
		return GetLen(*this, ChVector4());
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Abs()
	{
		val.Abs();
	}

	inline void Abs(const ChVector4& _vec)
	{
		val.Abs(_vec.val);
	}

	///////////////////////////////////////////////////////////////////////////////////

	//補正を行う(Nowは0〜1)
	inline void Correction(
		const ChVector4& _start, const ChVector4& _end, const float _Now)
	{
		*this = GetCorrection(_start, _end, _Now);
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Normalize();

	///////////////////////////////////////////////////////////////////////////////////

	void Cross(const ChVector4& _vec1, const ChVector4& _vec2);

};

using ChVec4 = ChVector4;

///////////////////////////////////////////////////////////////////////////////////

struct ChVector3 : public ChMath::ChVector3Base<float>
{

	ChVector3& operator*=(const float& _num);
	ChVector3 operator*(const float& _num) const;
	ChVector3& operator/=(const float& _num);
	ChVector3 operator/(const float& _num) const;
	ChVector3& operator=(const float& _num);

	ChVector3& operator=(const ChVector3& _vec);
	ChVector3& operator-=(const ChVector3& _vec);
	ChVector3 operator-(const ChVector3& _vec) const;
	ChVector3& operator+=(const ChVector3& _vec);
	ChVector3 operator+(const ChVector3& _vec) const;
	ChVector3& operator*=(const ChVector3& _vec);
	ChVector3 operator*(const ChVector3& _vec) const;
	ChVector3& operator/=(const ChVector3& _vec);
	ChVector3 operator/(const ChVector3& _vec) const;

	bool operator==(const ChVector3& _vec)const
	{
		return (x == _vec.x && y == _vec.y && z == _vec.z);
	}

	bool operator!=(const ChVector3& _vec)const
	{
		return (x != _vec.x || y != _vec.y || z != _vec.z);
	}

	operator const ChVector4() const;
	operator const ChVector2() const;

	operator const D3DXVECTOR3() const;
	operator const D3DXVECTOR3* () const;

	operator const DirectX::XMFLOAT3() const;
	operator const DirectX::XMFLOAT3* () const;

	ChVector3& operator=(const D3DXVECTOR3&);
	ChVector3& operator=(const DirectX::XMFLOAT3&);

	ChVector3& operator=(const D3DXQUATERNION&);
	ChVector3& operator=(const DirectX::XMFLOAT4&);

	ChVector3& operator=(const D3DXMATRIX&);
	ChVector3& operator=(const DirectX::XMFLOAT4X4&);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChVector3()
	{
		val.Identity();
	}

	inline ChVector3(const float _num)
	{
		val.Set(_num);
	}

	inline ChVector3(
		const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	inline ChVector3(const ChVector3& _vec) { *this = _vec; }

	inline ChVector3(const D3DXVECTOR3& _vec) { *this = _vec; }
	inline ChVector3(const DirectX::XMFLOAT3& _vec) { *this = _vec; }

	inline ChVector3(const D3DXQUATERNION& _Qua) { *this = _Qua; }
	inline ChVector3(const DirectX::XMFLOAT4& _Qua) { *this = _Qua; }

	inline ChVector3(const D3DXMATRIX& _mat) { *this = _mat; }
	inline ChVector3(const DirectX::XMFLOAT4X4& _mat) { *this = _mat; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	static ChVector3 GetCross(
		const ChVector3& _vec1, const ChVector3& _vec2);

	static float GetCos(
		const ChVector3& _vec1, const ChVector3& _vec2);

	static float GetRadian(
		const ChVector3& _vec1, const ChVector3& _vec2);

	static float GetDot(
		const ChVector3& _vec1, const ChVector3& _vec2);

	//補正を行う(Nowは0〜1)
	static ChVector3 GetCorrection(
		const ChVector3& _start, const ChVector3& _end, const float _Now);

	static float GetLen(
		const ChVector3& _vec1, const ChVector3& _vec2);

	///////////////////////////////////////////////////////////////////////////////////

	inline float Len() const
	{
		return GetLen(*this, ChVector3());
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Abs()
	{
		val.Abs();
	}

	inline void Abs(const ChVector3& _vec)
	{
		val.Abs(_vec.val);
	}

	///////////////////////////////////////////////////////////////////////////////////

	//補正を行う(Nowは0〜1)
	inline void Correction(
		const ChVector3& _start, const ChVector3& _end, const float _Now)
	{
		*this = GetCorrection(_start, _end, _Now);
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Normalize();

	///////////////////////////////////////////////////////////////////////////////////

	void Cross(const ChVector3& _vec1, const ChVector3& _vec2);

};

using ChVec3 = ChVector3;

///////////////////////////////////////////////////////////////////////////////////

struct ChVector2 : public ChMath::ChVector2Base<float>
{

	ChVector2& operator*=(const float& _num);
	ChVector2 operator*(const float& _num) const;
	ChVector2& operator/=(const float& _num);
	ChVector2 operator/(const float& _num) const;
	ChVector2& operator=(const float& _num);

	ChVector2& operator=(const ChVector2& _vec);
	ChVector2& operator-=(const ChVector2& _vec);
	ChVector2 operator-(const ChVector2& _vec) const;
	ChVector2& operator+=(const ChVector2& _vec);
	ChVector2 operator+(const ChVector2& _vec) const;
	ChVector2& operator*=(const ChVector2& _vec);
	ChVector2 operator*(const ChVector2& _vec) const;
	ChVector2& operator/=(const ChVector2& _vec);
	ChVector2 operator/(const ChVector2& _vec) const;

	bool operator==(const ChVector2& _vec)const
	{
		return (x == _vec.x && y == _vec.y);
	}

	bool operator!=(const ChVector2& _vec)const
	{
		return (x != _vec.x || y != _vec.y);
	}

	operator const ChVector4() const;
	operator const ChVector3() const;

	operator const D3DXVECTOR2() const;
	operator const D3DXVECTOR2* () const;

	ChVector2& operator=(const D3DXVECTOR2&);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChVector2()
	{
		val.Identity();
	}

	inline ChVector2(const float _num)
	{
		val.Set(_num);
	}

	inline ChVector2(
		const float _x, const float _y)
	{
		x = _x;
		y = _y;
	}

	inline ChVector2(const ChVector2& _vec) { *this = _vec; }

	inline ChVector2(const D3DXVECTOR2& _vec) { *this = _vec; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	static ChVector2 GetCross(
		const ChVector2& _vec1, const ChVector2& _vec2);

	static float GetCos(
		const ChVector2& _vec1, const ChVector2& _vec2);

	static float GetRadian(
		const ChVector2& _vec1, const ChVector2& _vec2);

	static float GetDot(
		const ChVector2& _vec1, const ChVector2& _vec2);

	//補正を行う(Nowは0〜1)
	static ChVector2 GetCorrection(
		const ChVector2& _start, const ChVector2& _end, const float _Now);

	static float GetLen(
		const ChVector2& _vec1, const ChVector2& _vec2);

	///////////////////////////////////////////////////////////////////////////////////

	inline float Len() const
	{
		return GetLen(*this, ChVector2());
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Abs()
	{
		val.Abs();
	}

	inline void Abs(const ChVector2& _vec)
	{
		val.Abs(_vec.val);
	}

	///////////////////////////////////////////////////////////////////////////////////

	//補正を行う(Nowは0〜1)
	inline void Correction(
		const ChVector2& _start, const ChVector2& _end, const float _Now)
	{
		*this = GetCorrection(_start, _end, _Now);
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Normalize();

	///////////////////////////////////////////////////////////////////////////////////

	void Cross(const ChVector2& _vec1, const ChVector2& _vec2);

};

using ChVec2 = ChVector2;

///////////////////////////////////////////////////////////////////////////////////

struct ChQuaternion : public ChMath::ChQuaternionBase
{

	operator const D3DXQUATERNION() const;
	operator const D3DXQUATERNION* () const;

	operator const DirectX::XMFLOAT4() const;
	operator const DirectX::XMFLOAT4* () const;

	ChQuaternion& operator=(const D3DXVECTOR3&);
	ChQuaternion& operator=(const DirectX::XMFLOAT3&);

	ChQuaternion& operator=(const D3DXQUATERNION&);
	ChQuaternion& operator=(const DirectX::XMFLOAT4&);

	ChQuaternion& operator=(const D3DXMATRIX&);
	ChQuaternion& operator=(const DirectX::XMFLOAT4X4&);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChQuaternion()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	inline ChQuaternion(const float _num)
	{
		x = _num;
		y = _num;
		z = _num;
	}

	inline ChQuaternion(
		const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	inline ChQuaternion(const ChQuaternion& _Qua) { *this = _Qua; }

	inline ChQuaternion(const D3DXVECTOR3& _vec) { *this = _vec; }
	inline ChQuaternion(const DirectX::XMFLOAT3& _vec) { *this = _vec; }

	inline ChQuaternion(const D3DXQUATERNION& _Qua) { *this = _Qua; }
	inline ChQuaternion(const DirectX::XMFLOAT4& _Qua) { *this = _Qua; }

	inline ChQuaternion(const D3DXMATRIX& _mat) { *this = _mat; }
	inline ChQuaternion(const DirectX::XMFLOAT4X4& _mat) { *this = _mat; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0,
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	ChVec3 GetEulerAngleForVec3() const;

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotYPR(const ChVec3& _vec)
	{
		RotYPR(_vec.x, _vec.y, _vec.z);
	}

	void RotYPR(
		const float _x, const float _y, const float _z);

};

using ChQua = ChQuaternion;

struct ChLMatrix;
struct ChRMatrix;

//LeftHandAxisMatrix//
struct ChLMatrix : public ChMath::ChBaseMatrix4x4<float>
{
	///////////////////////////////////////////////////////////////////////////////////
	//Operator//

	ChLMatrix& operator =(const ChLMatrix _mat);

	ChLMatrix& operator *= (const ChLMatrix _mat);
	ChLMatrix const operator * (const ChLMatrix _mat)const;

	ChLMatrix& operator += (const ChLMatrix _mat);
	ChLMatrix const operator + (const ChLMatrix _mat)const;

	ChLMatrix& operator -= (const ChLMatrix _mat);
	ChLMatrix const operator - (const ChLMatrix _mat)const;

	operator const D3DXMATRIX() const;
	operator const D3DXMATRIX* () const;

	operator const DirectX::XMFLOAT4X4() const;
	operator const DirectX::XMFLOAT4X4* () const;

	ChLMatrix& operator=(const D3DXVECTOR3&);
	ChLMatrix& operator=(const DirectX::XMFLOAT3&);

	ChLMatrix& operator=(const D3DXQUATERNION&);
	ChLMatrix& operator=(const DirectX::XMFLOAT4&);

	ChLMatrix& operator=(const D3DXMATRIX&);
	ChLMatrix& operator=(const DirectX::XMFLOAT4X4&);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChLMatrix()
	{
		Identity();
	}

	inline ChLMatrix(const ChLMatrix& _mat) { m.Set(_mat.m); }

	inline ChLMatrix(const D3DXVECTOR3& _vec) { *this = _vec; }
	inline ChLMatrix(const DirectX::XMFLOAT3& _vec) { *this = _vec; }

	inline ChLMatrix(const D3DXQUATERNION& _Qua) { *this = _Qua; }
	inline ChLMatrix(const DirectX::XMFLOAT4& _Qua) { *this = _Qua; }

	inline ChLMatrix(const D3DXMATRIX& _mat) { *this = _mat; }
	inline ChLMatrix(const DirectX::XMFLOAT4X4& _mat) { *this = _mat; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	std::string SerializeUpper(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const std::string& _cutTo4Char = "\n");

	void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6);


	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	void SetPosition(const ChVec3& _vec);

	void SetPosition(const float _x, const float _y, const float _z);

	void SetRotation(const ChVec3& _vec);

	void SetRotation(const float _x, const float _y, const float _z);

	void SetRotationXAxis(const float _x);

	void SetRotationYAxis(const float _y);

	void SetRotationZAxis(const float _z);

	void SetScalling(const ChVec3& _vec);

	void SetScalling(const float _x, const float _y, const float _z);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	ChVec3 GetPosition()const;

	ChVec3 GetRotation()const;

	ChVec3 GetScalling()const;

	ChMath::MatrixBase<float, 3, 3> GetRotMatrix()const;

	///////////////////////////////////////////////////////////////////////////////////

	ChVec4 Transform(const ChVec4 _Base)const;

	ChVec4 TransformCoord(const ChVec4 _Base)const;

	///////////////////////////////////////////////////////////////////////////////////

	void Identity()
	{
		m.Identity();
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Inverse()
	{

		ChLMatrix TmpMat = *this;
		ChLMatrix Addl;

		float Tmp[24];

		unsigned char Count = 0;

		//for (unsigned char i = 0; i < 4; i++)
		//{
		//	for (unsigned char j = 0; j < 4; j++)
		//	{
		//		for (unsigned char k = 0; k < 4; k++)
		//		{
		//			for (unsigned char l = 0; l < 4; l++)
		//			{

		//				if (j != i && j != k && i != k && j != l && i != l && k != l)
		//				{
		//					Tmp[Count] = m[0][i] * m[1][j] * m[2][k] * m[3][l];

		//					Count++;
		//				}
		//				



		//			}
		//		}
		//	}
		//}

		for (unsigned char i = 0; i < 4; i++)
		{
			for (unsigned char j = 0; j < 3; j++)
			{
				for (unsigned char k = 0; k < 2; k++)
				{
					Tmp[Count] = m[0][j] *
						m[1][j] *
						m[2][k] *
						m[3][0];

					Count++;
				}
			}
		}

		float Sum = Tmp[0];
		ChStd::Bool Flg = true;

		for (unsigned char i = 0; i < 23; i++)
		{
			Sum = (Flg) ? Sum - Tmp[i + 1] : Sum + Tmp[i + 1];

			Flg = (i + 1 % 2 == 0) ? -Flg : Flg;

		}

		if (Sum == 0.0f)return;

	}

	///////////////////////////////////////////////////////////////////////////////////

	ChRMatrix ConvertAxis();

};

//RightHandAxisMatrix//
struct ChRMatrix : public ChMath::ChBaseMatrix4x4<float>
{
	ChRMatrix& operator =(const ChRMatrix& _mat);

	//ChRMatrix& operator=(const D3DXVECTOR3&);
	//ChRMatrix& operator=(const DirectX::XMFLOAT3&);

	//ChRMatrix& operator=(const D3DXQUATERNION&);
	//ChRMatrix& operator=(const DirectX::XMFLOAT4&);

	//ChRMatrix& operator=(const D3DXMATRIX&);
	//ChRMatrix& operator=(const DirectX::XMFLOAT4X4&);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChRMatrix()
	{
		for (unsigned char i = 0; i < 4; i++)
		{
			for (unsigned char j = 0; j < 4; j++)
			{
				m[i][j] = i != j ? 0.0f : 1.0f;
			}
		}
	}

	inline ChRMatrix(const ChRMatrix& _mat) { *this = _mat; }

	//inline ChRMatrix(const D3DXVECTOR3& _vec) { *this = _vec; }
	//inline ChRMatrix(const DirectX::XMFLOAT3& _vec) { *this = _vec; }

	//inline ChRMatrix(const D3DXQUATERNION& _Qua) { *this = _Qua; }
	//inline ChRMatrix(const DirectX::XMFLOAT4& _Qua) { *this = _Qua; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	std::string SerializeUpper(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const std::string& _cutTo4Char = "\n");

	void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const unsigned int _digit = 6);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	ChVec3 GetPosition();

	ChVec3 GetRotation();

	ChVec3 GetScalling();


	ChLMatrix ConvertAxis();

};

using ChRMat = ChRMatrix;
using ChLMat = ChLMatrix;

struct ChUIMatrix : public ChMath::ChBaseMatrix4x4<unsigned long>
{
	///////////////////////////////////////////////////////////////////////////////////
	//Operator//

	ChUIMatrix& operator =(const ChUIMatrix _mat);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChUIMatrix()
	{
		m.Set(0UL);
	}

	inline ChUIMatrix(const ChUIMatrix& _mat) { m.Set(_mat.m); }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	std::string SerializeUpper(
		const std::string& _cutChar = ","
		, const std::string& _endChar = ";"
		, const std::string& _cutTo4Char = "\n");

	void Deserialize(
		const std::string& _str
		, const size_t _fPos = 0
		, const std::string& _cutChar = ","
		, const std::string& _endChar = ";");

	///////////////////////////////////////////////////////////////////////////////////

};

using ChUIMat = ChUIMatrix;

namespace ChMath
{

	static inline std::string ConvertNum10to64(unsigned long _num)
	{
		return "";
	}

	float Round(const float& _val, const unsigned int _digit);
	double Round(const double& _val, const unsigned int _digit);


	//円周率//
	static const float Pi = 3.1415f;

	class Degree;
	class Radian;

	//度数法であらわされた角度を取りまとめるクラス//
	class Degree
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//operator
		///////////////////////////////////////////////////////////////////////////////////

		inline Degree& operator=(const Degree _num)
		{
			val = _num;
			return *this;
		}

		Degree& operator=(const float _num);
		Degree& operator=(const Radian _num);

		Degree& operator+=(const float _num);
		Degree operator+(const float _num) const;

		Degree& operator-=(const float _num);
		Degree operator-(const float _num) const;

		Degree& operator*=(const float _num);
		Degree operator*(const float _num) const;

		Degree& operator/=(const float _num);
		Degree operator/(const float _num) const;

		operator float() const;

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer
		///////////////////////////////////////////////////////////////////////////////////

		Degree();

		Degree(const float _val);

		Degree(const Degree& _val);

		Degree(const Radian& _val);

		///////////////////////////////////////////////////////////////////////////////////

	private:
		void Math();

		float val;
	};

	//弧度法(円周率)であらわされた角度を取りまとめるクラス//
	class Radian
	{

	public:
		///////////////////////////////////////////////////////////////////////////////////
		//operator
		///////////////////////////////////////////////////////////////////////////////////

		inline Radian operator=(const Radian _num)
		{
			val = _num;
			return *this;
		}

		Radian& operator=(const float _num);
		Radian& operator=(const Degree _num);

		Radian& operator+=(const float _num);
		Radian operator+(const float _num) const;

		Radian& operator-=(const float _num);
		Radian operator-(const float _num) const;

		Radian& operator*=(const float _num);
		Radian operator*(const float _num) const;

		Radian& operator/=(const float _num);
		Radian operator/(const float _num) const;

		operator float() const;

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer
		///////////////////////////////////////////////////////////////////////////////////

		Radian();

		Radian(const float _val);

		Radian(const Radian& _val);

		Radian(const Degree& _val);

		///////////////////////////////////////////////////////////////////////////////////

	private:
		void Math();

		float val;
	};

	//三角面を構成する3頂点をまとめたもの//
	typedef struct TriVertex
	{
		ChVec3 Ver1, Ver2, Ver3;
		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline TriVertex() {}

		inline TriVertex(
			const ChVec3& _1, const ChVec3& _2, const ChVec3& _3)
		{
			Ver1 = _1;
			Ver2 = _2;
			Ver3 = _3;
		}

	} TriVer;

	//3頂点より法線を作成する//
	//法線は三頂点の外積(交差するベクトル)を算出して作成される//
	ChVector3 GetFaceNormal(const TriVertex& _PlEq);

	ChVector3 GetFaceNormal(
		const ChVec3& _Pos1, const ChVec3& _Pos2, const ChVec3& _Pos3);

	//Radian角からDegree角へ//
	static inline float ToDegree(const float _Radian) { return (_Radian * 180.0f / Pi); }

	//Degree角からRadian角へ//
	static inline float ToRadian(const float _degree) { return (_degree * Pi / 180.0f); }

	//正の符号かどうかを確認する//
	static inline ChStd::Bool IsPSign(const int _val) { return _val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const char _val) { return _val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const short _val) { return _val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const long _val) { return _val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const float _val) { return _val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const double _val) { return _val >= 0.0f ? true : false; }

} // namespace ChMath

#endif