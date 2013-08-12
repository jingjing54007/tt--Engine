//    __  __      ______            _          
//   / /_/ /__ _ / ____/___  ____ _(_)___  ___ 
//  / __/ __(_|_) __/ / __ \/ __ `/ / __ \/ _ \
// / /_/ /__ _ / /___/ / / / /_/ / / / / /  __/
// \__/\__(_|_)_____/_/ /_/\__, /_/_/ /_/\___/ 
//                        /____/               
//
// Namespace.h : File containing tt::Engine datatypes
//

#pragma once
#include "stdafx.h"
#include "D3DUtil.h"

class AbstractGame;

//Forward declarations
namespace tt
{
	struct Vector2;
	struct Vector3;
	struct Vector4;
	struct Matrix3x3;
	struct Matrix4x4;
	struct Quaternion;
	struct ViewportInfo;
	struct GameContext;
};

//Integration of tt::Engine datatypes and standard library
namespace std
{
	std::tstring to_tstring(const tt::Vector2& vec);
	std::tstring to_tstring(const tt::Vector3& vec);
	std::tstring to_tstring(const tt::Vector4& vec);
	std::tstring to_tstring(const tt::Matrix3x3& vec);
	std::tstring to_tstring(const tt::Matrix4x4& vec);
	std::tstringstream& operator<<(std::tstringstream& stream, const tt::Vector2& vec);
	std::tstringstream& operator<<(std::tstringstream& stream, const tt::Vector3& vec);
	std::tstringstream& operator<<(std::tstringstream& stream, const tt::Vector4& vec);
	std::tstringstream& operator<<(std::tstringstream& stream, const tt::Matrix3x3& vec);
	std::tstringstream& operator<<(std::tstringstream& stream, const tt::Matrix4x4& vec);
};

namespace tt
{
	//Vector consisting of 2 float components, support for common mathematical operations is provided
	struct Vector2
	{
		float x,y;

		Vector2(void);
		explicit Vector2(float f);
		Vector2(float _x, float _y);
		explicit Vector2(const D3DXVECTOR2& v);
		
		Vector2 operator+(const Vector2& v) const;
		Vector2& operator+=(const Vector2& v);
		Vector2 operator-(const Vector2& v) const;
		Vector2& operator-=(const Vector2& v);
		Vector2 operator*(float f) const;
		Vector2& operator*=(float f);
		Vector2 operator/(float f) const;
		Vector2& operator/=(float f);
		operator D3DXVECTOR2(void) const;

		Vector2& Normalize(void);
		static Vector2 Normalize(const Vector2& vec);
		float Length(void) const;
		float LengthSq(void) const;
	};

	//Vector consisting of 3 float components, support for common mathematical operations is provided
	struct Vector3
	{
		float x,y,z;

		Vector3(void);
		explicit Vector3(float f);
		Vector3(float _x, float _y, float _z);
		Vector3(const D3DXVECTOR3& v);
		Vector3(const D3DXVECTOR4& v);
				
		Vector3 operator+(const Vector3& v) const;
		Vector3& operator+=(const Vector3& v);
		Vector3 operator-(const Vector3& v) const;
		Vector3 operator-(void) const;
		Vector3& operator-=(const Vector3& v);
		Vector3 operator*(float f) const;
		Vector3& operator*=(float f);
		Vector3 operator*(const Vector3& v) const;
		Vector3& operator*=(const Vector3& v);
		Vector3 operator/(float f) const;
		Vector3& operator/=(float f);
		bool operator==(const Vector3& v) const;
		bool operator!=(const Vector3& v) const;
		operator D3DXVECTOR3(void) const;
		operator NxVec3(void) const;

		Vector3& Normalize(void);
		static Vector3 Normalize(const Vector3& vec);
		float Length(void) const;
		float LengthSq(void) const;
		Vector3 TransformCoord(Matrix4x4 matTransform) const;
		Vector3 Cross(const Vector3& v) const;
	};
	
	//Vector consisting of 4 float components, support for common mathematical operations is provided
	struct Vector4
	{
		float x,y,z,w;

		Vector4(void);
		explicit Vector4(float f);
		Vector4(float _x, float _y, float _z, float _w);
		Vector4(const D3DXVECTOR4& v);
		
		Vector4 operator+(const Vector4& v) const;
		Vector4& operator+=(const Vector4& v);
		Vector4 operator-(const Vector4& v) const;
		Vector4& operator-=(const Vector4& v);
		Vector4 operator*(float f) const;
		Vector4& operator*=(float f);
		Vector4 operator/(float f) const;
		Vector4& operator/=(float f);
		operator D3DXVECTOR4(void) const;

		Vector4& Normalize(void);
		static Vector4 Normalize(const Vector4& vec);
		float Length(void) const;
		float LengthSq(void) const;
	};

	struct Matrix3x3
	{
		float	_11, _12, _13,
				_21, _22, _23,
				_31, _32, _33;
	};

	struct Matrix4x4
	{
		float	_11, _12, _13, _14,
				_21, _22, _23, _24,
				_31, _32, _33, _34,
				_41, _42, _43, _44;

		static Matrix4x4 Identity(void);
		static Matrix4x4 Translation(Vector3 displacement);
		static Matrix4x4 Rotation(Quaternion rotationQuaternion);
		static Matrix4x4 Scale(Vector3 scale);
		static Matrix4x4 Scale(float scale);

		Matrix4x4(void);
		Matrix4x4(const D3DXMATRIX& mat);
		Matrix4x4(float __11, float __12, float __13, float __14
				,float __21, float __22, float __23, float __24
				,float __31, float __32, float __33, float __34
				,float __41, float __42, float __43, float __44);
		Matrix4x4 operator*(const Matrix4x4& mat) const;
		Matrix4x4& operator*=(const Matrix4x4& mat);

		void Decompose(Vector3& pos, Quaternion& rot, Vector3& scale) const;
		tt::Matrix4x4 Inverse(void) const;

		D3DXMATRIX To_DxMatrix(void) const;
	};
	
	struct Quaternion
	{
		float x,y,z,w;

		Quaternion(void);
		Quaternion(const Quaternion& quat);
		Quaternion(float _x, float _y, float _z, float _w);
		Quaternion(D3DXQUATERNION quat);
		
		Quaternion operator*(const Quaternion& quat) const;
		Quaternion& operator*=(const Quaternion& quat);

		bool operator==(const Quaternion& quat);
		bool operator!=(const Quaternion& quat);

		static Quaternion Identity(void);
		static Quaternion FromEuler(const Vector3& eulerAngles);
		static Quaternion FromEuler(float yaw, float pitch, float roll);
		
		operator D3DXQUATERNION(void) const;
	};

	struct ViewportInfo{
		ViewportInfo(void);
		ViewportInfo(unsigned short _width, unsigned short _height);

		unsigned short width, height;
	};

	struct GameContext
	{
		ViewportInfo vpInfo;
		AbstractGame* pGame;
		//Viewport size
		//DeltaTime
		//Camera
	};
};

tt::Vector3 operator*(float f,const tt::Vector3& v);