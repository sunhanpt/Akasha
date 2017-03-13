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

	CMatrix4<T>& makeIndentity();

	operator *(CMatrix4<T>& other)
	{
		for(int i = 0; i < )
	}
};

typedef CMatrix4<f32> matrix4f;

}

} // end namespace aka

#endif

