// vector3d: 3dœÚ¡ø¿‡

#ifndef __AKA_VECTOR3D_H_INCLUDED__
#define __AKA_VECTOR3D_H_INCLUDED__
#include "AkaMath.h"


namespace aka
{
namespace core
{

template<class T>
struct vector3d
{
	union
	{
		struct 
		{
			T x, y, z;
		};
		T v[3];
	};
	
	vector3d() : x(0), y(0), z(0) {}
	vector3d(T nx, T ny, T nz) :x(nx), y(ny), z(nz) {}
	explicit vector3d(T n) : X(n), Y(n), Z(n) {}

	vector3d<T> operator+(const vector3d<T>& other){ return vector3d<T>(x + other.x, y + other.y, z + other.z); }
	vector3d<T>& operator+=(const vector3d<T>& other) { x += other.x; y += other.y; z += other.z; return *this; }

	vector3d<T> operator-(const vector3d<T>& other){ return vector3d<T>(x - other.x, y - other.y, z - other.z); }
	vector3d<T>& operator-=(const vector3d<T>& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }

	vector3d<T> operator*(const T v) { return vector3d<T>(x * v, y * v, z * v); }
	vector3d<T>& operator*=(const T v) { x *= v; y *= v; z *= v; return *this; }

	vector3d<T> operator*(const vector3d<T>& other) { return vector3d<T>(x * other.x, y * other.y, z * other.z); }
	vector3d<T>& operator*=(const vector3d<T>& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }

	vector3d<T> operator/(const T v) { return vector3d<T>(x / v, y / v, z / v); }
	vector3d<T>& operator/=(const T v) { x /= v; y *= v; z *= v; return *this; }

	vector3d<T> operator/(const vector3d<T>& other) { return vector3d<T>(x / other.x, y / other.y, z / other.z); }
	vector3d<T>& operator/=(const vector3d<T>& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

	T getLength()
	{
		f64 lensq = x * x + y * y + z * z;
		f64 len = core::squareroot(lensq);
		return (T)len;
	}

	vector3d<T>& normalize()
	{
		f64 lensq = x * x + y * y + z * z;
		f64 recilen = core::reciprocal_squareroot(lensq);
		x = T(x * lensq);
		y = T(y * lensq);
		z = T(z * lensq);

		return *this;
	}

	vector3d<T> cross(vector3d<T>& other)
	{
		return vector3d<T>(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}
};

typedef vector3d<f32> vector3df;
typedef vector3d<s32> vector3di;
}

} // end namespace aka

#endif

