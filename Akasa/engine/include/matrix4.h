// matrix4

#ifndef __AKA_MATRIX4_H_INCLUDED__
#define __AKA_MATRIX4_H_INCLUDED__
#include "AkaMath.h"
#include "vector3d.h"

namespace aka
{
namespace core
{
	enum eConstructor
	{
		EM4CONST_NOTHING = 0,
		EM4CONST_COPY,
		EM4CONST_IDENTITY,
		EM4CONST_TRANSPOSED,
		EM4CONST_INVERSE,
		EM4CONST_INVERSE_TRANSPOSED
	};

template<class T>
class CMatrix4
{
public:
	union
	{
		struct 
		{
			T _11, _12, _13, _14;
			T _21, _22, _23, _24;
			T _31, _32, _33, _34;
			T _41, _42, _43, _44;
		};
		T m[16];
	};

	CMatrix4(eConstructor eType = EM4CONST_IDENTITY);

	CMatrix4(CMatrix4<T>& other, eConstructor eType = EM4CONST_COPY);

	T& operator()(int row, int colum) { return m[row * 4 + colum]; }

	const T& operator()(int row, int colum) { return m[row * 4 + colum]; }

	T& operator[](int index) { return m[index]; }

	const T& operator[](int index) { return m[index]; }

	T* pointer() { return m; }
	const T* pointer() { return m; }

	CMatrix4<T>& operator= (const CMatrix4<T>& other);

	CMatrix4<T>& operator= (const T v);

	CMatrix4<T> operator+ (const CMatrix4<T>& other) const;
	CMatrix4<T>& operator+= (const CMatrix4<T>& other);

	CMatrix4<T> operator- (const CMatrix4<T>& other) const;
	CMatrix4<T>& operator-= (const CMatrix4<T>& other);


	CMatrix4<T> operator *(CMatrix4<T>& other) const;
	CMatrix4<T>& operator *=(CMatrix4<T>& other);

	CMatrix4<T> operator *(T v) const;
	CMatrix4<T>& operator *=(T v);

	CMatrix4<T> operator /(T v) const;
	CMatrix4<T>& operator /=(T v);

	CMatrix4<T>& makeIndentity();

	CMatrix4<T> getTransposed();

	bool getInverse(CMatrix4<T>& out);

};

typedef CMatrix4<f32> matrix4f;

template<class T>
inline CMatrix4<T>::CMatrix4(eConstructor eType)
{
	memset(m, 0, sizeof(T) * 16);
	if (eType == core::EM4CONST_IDENTITY) {
		makeIndentity();
	}
}

template<class T>
inline CMatrix4<T>::CMatrix4(CMatrix4<T>& other, eConstructor eType)
{
	switch (eType)
	{
	case aka::core::EM4CONST_NOTHING:
		memset(m, 0, sizeof(T) * 16);
		break;
	case aka::core::EM4CONST_COPY:
		*this = other;
		break;
	case aka::core::EM4CONST_IDENTITY:
		makeIndentity();
		break;
	case aka::core::EM4CONST_TRANSPOSED:
		*this = other.getTransposed();
		break;
	case aka::core::EM4CONST_INVERSE:
		*this = other.getInverse();
		break;
	case aka::core::EM4CONST_INVERSE_TRANSPOSED:
		if (!other.getInverse(*this)) {
			memset(m, 0, sizeof(T) * 16);
		}
		else {
			*this = this->getTransposed();
		}
		break;
	default:
		break;
	}
}

template<class T>
inline CMatrix4<T>& CMatrix4<T>::operator=(const CMatrix4<T>& other)
{
	memcpy(this->m, other.m, sizeof(T) * 16);
	return *this;
}

template<class T>
inline CMatrix4<T>& CMatrix4<T>::operator=(const T v)
{
	for (int i = 0; i < 16; i++) {
		m[i] = v;
	}
	return *this;
}

template<class T>
inline CMatrix4<T> CMatrix4<T>::operator+(const CMatrix4<T>& other) const
{
	CMatrix4<T> t();
	for (int i = 0; i < 16; i++) {
		t.m[i] = this->m[i] + other.m[i];
	}
	 
}

template<class T>
inline CMatrix4<T>& CMatrix4<T>::operator+=(const CMatrix4<T>& other)
{
	for (int i = 0; i < 16; i++) {
		this->m[i] += other.m[i];
	}
	return *this;
}

template<class T>
inline CMatrix4<T> CMatrix4<T>::operator-(const CMatrix4<T>& other)
{
	CMatrix4<T> t();
	for (int i = 0; i < 16; i++) {
		t.m[i] = this->m[i] - other.m[i];
	}
}

template<class T>
inline CMatrix4<T> CMatrix4<T>::operator-(const CMatrix4<T>& other) const
{
	return CMatrix4<T>();
}

template<class T>
inline CMatrix4<T>& CMatrix4<T>::operator-=(const CMatrix4<T>& other)
{
	for (int i = 0; i < 16; i++) {
		this->m[i] -= other.m[i];
	}
	return *this;
}

template<class T>
inline CMatrix4<T> CMatrix4<T>::operator*(CMatrix4<T>& other) const
{
	CMatrix4<T> t(EM4CONST_NOTHING);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; ++) {
				t(i, j) += this->(i, k) * other(k,j);
			}
		}
	}
	return t;
}

template<class T>
inline CMatrix4<T>& CMatrix4<T>::operator*=(CMatrix4<T>& other)
{
	*this = *this * other;
	return *this;
}

template<class T>
inline CMatrix4<T> CMatrix4<T>::operator*(T v) const
{
	return CMatrix4<T> t(EM4CONST_NOTHING);
	for (int i = 0; i < 16; i++) {
		t.m[i] = this->m[i] * v;
	}
	return t;
}

template<class T>
inline CMatrix4<T>& CMatrix4<T>::operator*=(T v)
{
	for (int i = 0; i < 16; i++) {
		this->m[i] *= v;
	}
	return *this;
}

template<class T>
inline CMatrix4<T> CMatrix4<T>::operator/(T v) const
{
	CMatrix4<T> t(EM4CONST_NOTHING);
	for (int i = 0; i < 16; i++) {
		t.m[i] = this->m[i] / v;
	}
	return t;
}

template<class T>
inline CMatrix4<T>& CMatrix4<T>::operator/=(T v)
{
	for (int i = 0; i < 16; i++){
		this->m[i] /= v;
	}
	return *this;
}

template<class T>
inline CMatrix4<T>& CMatrix4<T>::makeIndentity()
{
	// TODO: 在此处插入 return 语句
	memset(m, 0, sizeof(T) * 16);
	for (int i = 0; i < 4; i++) {
		m[i * 4 + i] = (T)1;
	}
	return *this;
}

template<class T>
inline CMatrix4<T> CMatrix4<T>::getTransposed()
{
	CMatrix4<T> t(EM4CONST_NOTHING);
	t._11 = this->_11;
	t._12 = this->_21;
	t._13 = this->_31;
	t._14 = this->_41;

	t._21 = this->_12;
	t._22 = this->_22;
	t._23 = this->_32;
	t._24 = this->_42;

	t._31 = this->_13;
	t._32 = this->_23;
	t._33 = this->_33;
	t._34 = this->_43;

	t._41 = this->_14;
	t._42 = this->_24;
	t._43 = this->_34;
	t._44 = this->_44;

	return t;
}

template<class T>
inline bool CMatrix4<T>::getInverse(CMatrix4<T>& out)
{
	const CMatrix4<T> &m = *this;

	f32 d = (m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)) * (m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2)) -
		(m(0, 0) * m(1, 2) - m(0, 2) * m(1, 0)) * (m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1)) +
		(m(0, 0) * m(1, 3) - m(0, 3) * m(1, 0)) * (m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1)) +
		(m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * (m(2, 0) * m(3, 3) - m(2, 3) * m(3, 0)) -
		(m(0, 1) * m(1, 3) - m(0, 3) * m(1, 1)) * (m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0)) +
		(m(0, 2) * m(1, 3) - m(0, 3) * m(1, 2)) * (m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0));

	if (core::iszero(d, FLT_MIN))
		return false;

	d = core::reciprocal(d);

	out(0, 0) = d * (m(1, 1) * (m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2)) +
		m(1, 2) * (m(2, 3) * m(3, 1) - m(2, 1) * m(3, 3)) +
		m(1, 3) * (m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1)));
	out(0, 1) = d * (m(2, 1) * (m(0, 2) * m(3, 3) - m(0, 3) * m(3, 2)) +
		m(2, 2) * (m(0, 3) * m(3, 1) - m(0, 1) * m(3, 3)) +
		m(2, 3) * (m(0, 1) * m(3, 2) - m(0, 2) * m(3, 1)));
	out(0, 2) = d * (m(3, 1) * (m(0, 2) * m(1, 3) - m(0, 3) * m(1, 2)) +
		m(3, 2) * (m(0, 3) * m(1, 1) - m(0, 1) * m(1, 3)) +
		m(3, 3) * (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)));
	out(0, 3) = d * (m(0, 1) * (m(1, 3) * m(2, 2) - m(1, 2) * m(2, 3)) +
		m(0, 2) * (m(1, 1) * m(2, 3) - m(1, 3) * m(2, 1)) +
		m(0, 3) * (m(1, 2) * m(2, 1) - m(1, 1) * m(2, 2)));
	out(1, 0) = d * (m(1, 2) * (m(2, 0) * m(3, 3) - m(2, 3) * m(3, 0)) +
		m(1, 3) * (m(2, 2) * m(3, 0) - m(2, 0) * m(3, 2)) +
		m(1, 0) * (m(2, 3) * m(3, 2) - m(2, 2) * m(3, 3)));
	out(1, 1) = d * (m(2, 2) * (m(0, 0) * m(3, 3) - m(0, 3) * m(3, 0)) +
		m(2, 3) * (m(0, 2) * m(3, 0) - m(0, 0) * m(3, 2)) +
		m(2, 0) * (m(0, 3) * m(3, 2) - m(0, 2) * m(3, 3)));
	out(1, 2) = d * (m(3, 2) * (m(0, 0) * m(1, 3) - m(0, 3) * m(1, 0)) +
		m(3, 3) * (m(0, 2) * m(1, 0) - m(0, 0) * m(1, 2)) +
		m(3, 0) * (m(0, 3) * m(1, 2) - m(0, 2) * m(1, 3)));
	out(1, 3) = d * (m(0, 2) * (m(1, 3) * m(2, 0) - m(1, 0) * m(2, 3)) +
		m(0, 3) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0)) +
		m(0, 0) * (m(1, 2) * m(2, 3) - m(1, 3) * m(2, 2)));
	out(2, 0) = d * (m(1, 3) * (m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0)) +
		m(1, 0) * (m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1)) +
		m(1, 1) * (m(2, 3) * m(3, 0) - m(2, 0) * m(3, 3)));
	out(2, 1) = d * (m(2, 3) * (m(0, 0) * m(3, 1) - m(0, 1) * m(3, 0)) +
		m(2, 0) * (m(0, 1) * m(3, 3) - m(0, 3) * m(3, 1)) +
		m(2, 1) * (m(0, 3) * m(3, 0) - m(0, 0) * m(3, 3)));
	out(2, 2) = d * (m(3, 3) * (m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)) +
		m(3, 0) * (m(0, 1) * m(1, 3) - m(0, 3) * m(1, 1)) +
		m(3, 1) * (m(0, 3) * m(1, 0) - m(0, 0) * m(1, 3)));
	out(2, 3) = d * (m(0, 3) * (m(1, 1) * m(2, 0) - m(1, 0) * m(2, 1)) +
		m(0, 0) * (m(1, 3) * m(2, 1) - m(1, 1) * m(2, 3)) +
		m(0, 1) * (m(1, 0) * m(2, 3) - m(1, 3) * m(2, 0)));
	out(3, 0) = d * (m(1, 0) * (m(2, 2) * m(3, 1) - m(2, 1) * m(3, 2)) +
		m(1, 1) * (m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0)) +
		m(1, 2) * (m(2, 1) * m(3, 0) - m(2, 0) * m(3, 1)));
	out(3, 1) = d * (m(2, 0) * (m(0, 2) * m(3, 1) - m(0, 1) * m(3, 2)) +
		m(2, 1) * (m(0, 0) * m(3, 2) - m(0, 2) * m(3, 0)) +
		m(2, 2) * (m(0, 1) * m(3, 0) - m(0, 0) * m(3, 1)));
	out(3, 2) = d * (m(3, 0) * (m(0, 2) * m(1, 1) - m(0, 1) * m(1, 2)) +
		m(3, 1) * (m(0, 0) * m(1, 2) - m(0, 2) * m(1, 0)) +
		m(3, 2) * (m(0, 1) * m(1, 0) - m(0, 0) * m(1, 1)));
	out(3, 3) = d * (m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) +
		m(0, 1) * (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) +
		m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0)));

	return true;
}

}

} // end namespace aka

#endif

