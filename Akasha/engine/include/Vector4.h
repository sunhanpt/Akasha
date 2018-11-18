#pragma once

#include "CoreDefines.h"
#include "TypeDefines.h"
#include "Vector.h"
#include "MathUtility.h"

/**
 * A 4D homogeneous vector, 4x1 FLOATs, 16-byte aligned.
 */
MS_ALIGN(16) struct FVector4
{
public:

	float X, Y, Z, W;

public:

	FVector4(const FVector& InVector, float InW = 1.0f);
	explicit FVector4(float InX = 0.0f, float InY = 0.0f, float InZ = 0.0f, float InW = 1.0f);

public:

	FORCEINLINE float& operator[](int32 ComponentIndex);
	FORCEINLINE float operator[](int32 ComponentIndex) const;
	FORCEINLINE FVector4 operator-() const;
	FORCEINLINE FVector4 operator+(const FVector4& V) const;
	FORCEINLINE FVector4 operator+=(const FVector4& V);
	FORCEINLINE FVector4 operator-(const FVector4& V) const;
	FORCEINLINE FVector4 operator-=(const FVector4& V);
	FORCEINLINE FVector4 operator*(float Scale) const;
	FVector4 operator/(float Scale) const;
	FVector4 operator/(const FVector4& V) const;
	FVector4 operator*(const FVector4& V) const;
	FVector4 operator*=(const FVector4& V);
	FVector4 operator/=(const FVector4& V);
	FVector4 operator*=(float S);
	friend FORCEINLINE float Dot3(const FVector4& V1, const FVector4& V2)
	{
		return V1.X*V2.X + V1.Y*V2.Y + V1.Z*V2.Z;
	}
	friend FORCEINLINE float Dot4(const FVector4& V1, const FVector4& V2)
	{
		return V1.X*V2.X + V1.Y*V2.Y + V1.Z*V2.Z + V1.W*V2.W;
	}
	friend FORCEINLINE FVector4 operator*(float Scale, const FVector4& V)
	{
		return V.operator*(Scale);
	}
	bool operator==(const FVector4& V) const;
	bool operator!=(const FVector4& V) const;
	FVector4 operator^(const FVector4& V) const;

	bool Equals(const FVector4& V, float Tolerance = KINDA_SMALL_NUMBER) const;

public:

	FORCEINLINE void Set(float InX, float InY, float InZ, float InW);

public:
	AKADLL_API FRotator ToOrientationRotator() const;
	AKADLL_API FRotator Rotation() const;
	AKADLL_API FQuat ToOrientationQuat() const;
	FORCEINLINE FVector4 GetSafeNormal(float Tolerance = SMALL_NUMBER) const;
};


FORCEINLINE FVector4::FVector4(const FVector& InVector, float InW)
	: X(InVector.X)
	, Y(InVector.Y)
	, Z(InVector.Z)
	, W(InW)
{
}

FORCEINLINE FVector4::FVector4(float InX, float InY, float InZ, float InW)
	: X(InX)
	, Y(InY)
	, Z(InZ)
	, W(InW)
{
}

FORCEINLINE float& FVector4::operator[](int32 ComponentIndex)
{
	return (&X)[ ComponentIndex ];
}

FORCEINLINE float FVector4::operator[](int32 ComponentIndex) const
{
	return (&X)[ ComponentIndex ];
}

FORCEINLINE FVector4 FVector4::operator-() const
{
	return FVector4(-X, -Y, -Z, -W);
}

FORCEINLINE FVector4 FVector4::operator+(const FVector4& V) const
{
	return FVector4(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
}

FORCEINLINE FVector4 FVector4::operator+=(const FVector4& V)
{
	X += V.X; Y += V.Y; Z += V.Z; W += V.W;
	return *this;
}

FORCEINLINE FVector4 FVector4::operator-(const FVector4& V) const
{
	return FVector4(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
}

FORCEINLINE FVector4 FVector4::operator-=(const FVector4& V)
{
	X -= V.X; Y -= V.Y; Z -= V.Z; W -= V.W;
	return *this;
}

FORCEINLINE FVector4 FVector4::operator*(float Scale) const
{
	return FVector4(X * Scale, Y * Scale, Z * Scale, W * Scale);
}

FORCEINLINE FVector4 FVector4::operator/(float Scale) const
{
	const float RScale = 1.f/Scale;
	return FVector4(X * RScale, Y * RScale, Z * RScale, W * RScale);
}

FORCEINLINE FVector4 FVector4::operator*(const FVector4& V) const
{
	return FVector4(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
}

FORCEINLINE FVector4 FVector4::operator^(const FVector4& V) const
{
	return FVector4(
		Y * V.Z - Z * V.Y,
		Z * V.X - X * V.Z,
		X * V.Y - Y * V.X,
		0.0f
	);
}

FORCEINLINE bool FVector4::operator==(const FVector4& V) const
{
	return ((X == V.X) && (Y == V.Y) && (Z == V.Z) && (W == V.W));
}

FORCEINLINE bool FVector4::operator!=(const FVector4& V) const
{
	return ((X != V.X) || (Y != V.Y) || (Z != V.Z) || (W != V.W));
}

FORCEINLINE FVector4 FVector4::operator*=(const FVector4& V)
{
	X *= V.X; Y *= V.Y; Z *= V.Z; W *= V.W;
	return *this;
}

FORCEINLINE FVector4 FVector4::operator/=(const FVector4& V)
{
	X /= V.X; Y /= V.Y; Z /= V.Z; W /= V.W;
	return *this;
}

FORCEINLINE FVector4 FVector4::operator*=(float S)
{
	X *= S; Y *= S; Z *= S; W *= S;
	return *this;
}

FORCEINLINE FVector4 FVector4::operator/(const FVector4& V) const
{
	return FVector4(X / V.X, Y / V.Y, Z / V.Z, W / V.W);
}

FORCEINLINE bool FVector4::Equals(const FVector4& V, float Tolerance) const
{
	return FMath::Abs(X - V.X) <= Tolerance && FMath::Abs(Y - V.Y) <= Tolerance && FMath::Abs(Z - V.Z) <= Tolerance && FMath::Abs(W - V.W) <= Tolerance;
}

FORCEINLINE void FVector4::Set(float InX, float InY, float InZ, float InW)
{
	X = InX;
	Y = InY;
	Z = InZ;
	W = InW;
}

FORCEINLINE FVector4 FVector4::GetSafeNormal(float Tolerance) const
{
	const float SquareSum = X*X + Y*Y + Z*Z;
	if (SquareSum > Tolerance)
	{
		const float Scale = FMath::InvSqrt(SquareSum);
		return FVector4(X*Scale, Y*Scale, Z*Scale, 0.0f);
	}
	return FVector4(0.f);
}



/////////////////////////////////////*Vector*/////////////////////////////////////
FORCEINLINE FVector::FVector(const FVector4& V)
{
	X = V.X;
	Y = V.Y;
	Z = V.Z;
}