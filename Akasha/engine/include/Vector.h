#pragma once

#include "CoreDefines.h"
#include "TypeDefines.h"
#include "Vector2D.h"

struct FVector4;
struct FQuat;
struct FRotator;

struct FVector
{
public:
	float X, Y, Z;

public:

	/** A zero vector (0,0,0) */
	static CORE_API const FVector ZeroVector;

	/** One vector (1,1,1) */
	static CORE_API const FVector OneVector;

	/** World up vector (0,0,1) */
	static CORE_API const FVector UpVector;

	/** Unreal forward vector (1,0,0) */
	static CORE_API const FVector ForwardVector;

	/** Unreal right vector (0,1,0) */
	static CORE_API const FVector RightVector;

public:
	FORCEINLINE static FVector CrossProduct(const FVector& A, const FVector& B);
	FORCEINLINE static float DotProduct(const FVector& A, const FVector& B);

public:
	FORCEINLINE FVector();
	explicit FORCEINLINE FVector(float Inf);
	FORCEINLINE FVector(float InX, float InY, float InZ);
	FORCEINLINE FVector(const FVector& Other);
	FORCEINLINE FVector(const FVector4& V);

public:
	FORCEINLINE FVector operator^(const FVector& V) const;			// 叉乘
	FORCEINLINE float operator|(const FVector& V) const;			// 点乘
	FORCEINLINE FVector operator+(const FVector& V) const;			// 向量加
	FORCEINLINE FVector operator-(const FVector& V) const;			// 向量减
	FORCEINLINE FVector operator-(float Bias) const;				// 向量减常数
	FORCEINLINE FVector operator+(float Bias) const;				// 向量加常数
	FORCEINLINE FVector operator*(float Scale) const;				// 向量乘常数
	FORCEINLINE FVector operator/(float Scale) const;				// 向量除常数
	FORCEINLINE FVector operator*(const FVector& V) const;			// 向量相乘
	FORCEINLINE FVector operator/(const FVector& V) const;			// 向量相除
	FORCEINLINE FVector operator+=(const FVector & V);
	FORCEINLINE FVector operator-=(const FVector & V);
	bool operator==(const FVector& V) const;
	bool operator!=(const FVector& V) const;
	bool Equals(const FVector& V, float Tolerance = KINDA_SMALL_NUMBER) const;
	bool AllComponentsEqual(float Tolerance = KINDA_SMALL_NUMBER) const;
	FORCEINLINE FVector operator-() const;
	float& operator[](int32 Index);
	float operator[](int32 Index)const;

public:
	float SizeSquared() const;
	bool Normalize(float Tolerance = SMALL_NUMBER);
	FVector GetSafeNormal(float Tolerance = SMALL_NUMBER) const;
	bool IsNearlyZero(float Tolerance = KINDA_SMALL_NUMBER) const;
	bool IsZero() const;
	float Size() const;

public:
	FVector MirrorByPlane(const FPlane& Plane) const;
	static FVector PointPlaneProject(const FVector& Point, const FPlane& Plane);
	static FVector PointPlaneProject(const FVector& Point, const FVector& A, const FVector& B, const FVector& C);
	static float PointPlaneDist(const FVector &Point, const FVector &PlaneBase, const FVector &PlaneNormal);
	static CORE_API void CreateOrthonormalBasis(FVector& XAxis, FVector& YAxis, FVector& ZAxis);
	static FORCEINLINE float Dist(const FVector &V1, const FVector &V2);
	static FORCEINLINE float DistSquared(const FVector &V1, const FVector &V2);
	static CORE_API float EvaluateBezier(const FVector* ControlPoints, int32 NumPoints, std::vector<FVector>& OutPoints);

	CORE_API FQuat ToOrientationQuat() const;

	CORE_API FRotator ToOrientationRotator() const;

	CORE_API FRotator Rotation() const;

	CORE_API void FindBestAxisVectors(FVector& Axis1, FVector& Axis2) const;

	CORE_API void UnwindEuler();

	FVector Reciprocal() const;

	FVector RotateAngleAxis(const float AngleDeg, const FVector& Axis) const;

};

FORCEINLINE FVector FVector::CrossProduct(const FVector& A, const FVector& B)
{
	return A ^ B;
}

FORCEINLINE float FVector::DotProduct(const FVector& A, const FVector& B)
{
	return A | B;
}

FORCEINLINE FVector::FVector()
{}

FORCEINLINE FVector::FVector(float InF)
	: X(InF), Y(InF), Z(InF)
{
}

FORCEINLINE FVector::FVector(float InX, float InY, float InZ)
	: X(InX), Y(InY), Z(InZ)
{
}

FORCEINLINE FVector::FVector(const FVector& Other)
	: X(Other.X), Y(Other.Y), Z(Other.Z)
{
}

FORCEINLINE FVector FVector::operator^(const FVector& V) const
{
	return FVector
	(
		Y * V.Z - Z * V.Y,
		Z * V.X - X * V.Z,
		X * V.Y - Y * V.X
	);
}

FORCEINLINE float FVector::operator|(const FVector& V) const
{
	return X*V.X + Y*V.Y + Z*V.Z;
}

FORCEINLINE FVector FVector::operator+(const FVector& V) const
{
	return FVector(X + V.X, Y + V.Y, Z + V.Z);
}

FORCEINLINE FVector FVector::operator-(const FVector& V) const
{
	return FVector(X - V.X, Y - V.Y, Z - V.Z);
}

FORCEINLINE FVector FVector::operator-(float Bias) const
{
	return FVector(X - Bias, Y - Bias, Z - Bias);
}

FORCEINLINE FVector FVector::operator+(float Bias) const
{
	return FVector(X + Bias, Y + Bias, Z + Bias);
}

FORCEINLINE FVector FVector::operator*(float Scale) const
{
	return FVector(X * Scale, Y * Scale, Z * Scale);
}

FORCEINLINE FVector FVector::operator/(float Scale) const
{
	const float RScale = 1.f / Scale;
	return FVector(X * RScale, Y * RScale, Z * RScale);
}

FORCEINLINE FVector FVector::operator*(const FVector& V) const
{
	return FVector(X * V.X, Y * V.Y, Z * V.Z);
}

FORCEINLINE FVector FVector::operator/(const FVector& V) const
{
	return FVector(X / V.X, Y / V.Y, Z / V.Z);
}

FORCEINLINE FVector FVector::operator+=(const FVector& V)
{
	X += V.X; Y += V.Y; Z += V.Z;
	return *this;
}

FORCEINLINE FVector FVector::operator-=(const FVector& V)
{
	X -= V.X; Y -= V.Y; Z -= V.Z;
	return *this;
}

FORCEINLINE bool FVector::operator==(const FVector& V) const
{
	return X == V.X && Y == V.Y && Z == V.Z;
}

FORCEINLINE bool FVector::operator!=(const FVector& V) const
{
	return X != V.X || Y != V.Y || Z != V.Z;
}

FORCEINLINE bool FVector::Equals(const FVector& V, float Tolerance) const
{
	return FMath::Abs(X - V.X) <= Tolerance && FMath::Abs(Y - V.Y) <= Tolerance && FMath::Abs(Z - V.Z) <= Tolerance;
}

FORCEINLINE bool FVector::AllComponentsEqual(float Tolerance) const
{
	return FMath::Abs(X - Y) <= Tolerance && FMath::Abs(X - Z) <= Tolerance && FMath::Abs(Y - Z) <= Tolerance;
}

FORCEINLINE FVector FVector::operator-() const
{
	return FVector(-X, -Y, -Z);
}

FORCEINLINE float& FVector::operator[](int32 Index)
{
	check(Index >= 0 && Index < 3);
	if (Index == 0)
	{
		return X;
	}
	else if (Index == 1)
	{
		return Y;
	}
	else
	{
		return Z;
	}
}

FORCEINLINE float FVector::operator[](int32 Index)const
{
	check(Index >= 0 && Index < 3);
	if (Index == 0)
	{
		return X;
	}
	else if (Index == 1)
	{
		return Y;
	}
	else
	{
		return Z;
	}
}

FORCEINLINE float FVector::SizeSquared() const
{
	return X*X + Y*Y + Z*Z;
}

FORCEINLINE bool FVector::Normalize(float Tolerance)
{
	const float SquareSum = X*X + Y*Y + Z*Z;
	if (SquareSum > Tolerance)
	{
		const float Scale = FMath::InvSqrt(SquareSum);
		X *= Scale; Y *= Scale; Z *= Scale;
		return true;
	}
	return false;
}

FORCEINLINE FVector FVector::GetSafeNormal(float Tolerance) const
{
	const float SquareSum = X*X + Y*Y + Z*Z;

	// Not sure if it's safe to add tolerance in there. Might introduce too many errors
	if (SquareSum == 1.f)
	{
		return *this;
	}
	else if (SquareSum < Tolerance)
	{
		return FVector::ZeroVector;
	}
	const float Scale = FMath::InvSqrt(SquareSum);
	return FVector(X*Scale, Y*Scale, Z*Scale);
}

FORCEINLINE bool FVector::IsNearlyZero(float Tolerance) const
{
	return
		FMath::Abs(X) <= Tolerance
		&&	FMath::Abs(Y) <= Tolerance
		&&	FMath::Abs(Z) <= Tolerance;
}

FORCEINLINE bool FVector::IsZero() const
{
	return X == 0.f && Y == 0.f && Z == 0.f;
}

FORCEINLINE float FVector::Size() const
{
	return FMath::Sqrt(X*X + Y*Y + Z*Z);
}

inline float FVector::PointPlaneDist
(
	const FVector &Point,
	const FVector &PlaneBase,
	const FVector &PlaneNormal
)
{
	return (Point - PlaneBase) | PlaneNormal;
}


FORCEINLINE float FVector::Dist(const FVector &V1, const FVector &V2)
{
	return FMath::Sqrt(FVector::DistSquared(V1, V2));
}

FORCEINLINE float FVector::DistSquared(const FVector &V1, const FVector &V2)
{
	return FMath::Square(V2.X - V1.X) + FMath::Square(V2.Y - V1.Y) + FMath::Square(V2.Z - V1.Z);
}

FORCEINLINE FVector operator*(float Scale, const FVector& V)
{
	return V.operator*(Scale);
}

/**
* Util to calculate distance from a point to a bounding box
*
* @param Mins 3D Point defining the lower values of the axis of the bound box
* @param Max 3D Point defining the lower values of the axis of the bound box
* @param Point 3D position of interest
* @return the distance from the Point to the bounding box.
*/
FORCEINLINE float ComputeSquaredDistanceFromBoxToPoint(const FVector& Mins, const FVector& Maxs, const FVector& Point)
{
	// Accumulates the distance as we iterate axis
	float DistSquared = 0.f;

	// Check each axis for min/max and add the distance accordingly
	// NOTE: Loop manually unrolled for > 2x speed up
	if (Point.X < Mins.X)
	{
		DistSquared += FMath::Square(Point.X - Mins.X);
	}
	else if (Point.X > Maxs.X)
	{
		DistSquared += FMath::Square(Point.X - Maxs.X);
	}

	if (Point.Y < Mins.Y)
	{
		DistSquared += FMath::Square(Point.Y - Mins.Y);
	}
	else if (Point.Y > Maxs.Y)
	{
		DistSquared += FMath::Square(Point.Y - Maxs.Y);
	}

	if (Point.Z < Mins.Z)
	{
		DistSquared += FMath::Square(Point.Z - Mins.Z);
	}
	else if (Point.Z > Maxs.Z)
	{
		DistSquared += FMath::Square(Point.Z - Maxs.Z);
	}

	return DistSquared;
}

/* FVector2D inline functions
*****************************************************************************/

FORCEINLINE FVector2D::FVector2D(const FVector& V)
	: X(V.X), Y(V.Y)
{
}

inline FVector FVector2D::SphericalToUnitCartesian() const
{
	const float SinTheta = FMath::Sin(X);
	return FVector(FMath::Cos(Y) * SinTheta, FMath::Sin(Y) * SinTheta, FMath::Cos(X));
}

/* FMath inline functions
*****************************************************************************/

inline FVector FMath::LinePlaneIntersection
(
	const FVector &Point1,
	const FVector &Point2,
	const FVector &PlaneOrigin,
	const FVector &PlaneNormal
)
{
	return
		Point1
		+ (Point2 - Point1)
		*	(((PlaneOrigin - Point1) | PlaneNormal) / ((Point2 - Point1) | PlaneNormal));
}

inline bool FMath::LineSphereIntersection(const FVector& Start, const FVector& Dir, float Length, const FVector& Origin, float Radius)
{
	const FVector	EO = Start - Origin;
	const float		v = (Dir | (Origin - Start));
	const float		disc = Radius * Radius - ((EO | EO) - v * v);

	if (disc >= 0.0f)
	{
		const float	Time = (v - Sqrt(disc)) / Length;

		if (Time >= 0.0f && Time <= 1.0f)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

FORCEINLINE FVector FVector::Reciprocal() const
{
	FVector RecVector;
	if (X != 0.f)
	{
		RecVector.X = 1.f / X;
	}
	else
	{
		RecVector.X = BIG_NUMBER;
	}
	if (Y != 0.f)
	{
		RecVector.Y = 1.f / Y;
	}
	else
	{
		RecVector.Y = BIG_NUMBER;
	}
	if (Z != 0.f)
	{
		RecVector.Z = 1.f / Z;
	}
	else
	{
		RecVector.Z = BIG_NUMBER;
	}

	return RecVector;
}

inline FVector FVector::RotateAngleAxis(const float AngleDeg, const FVector& Axis) const
{
	float S, C;
	FMath::SinCos(&S, &C, FMath::DegreesToRadians(AngleDeg));

	const float XX = Axis.X * Axis.X;
	const float YY = Axis.Y * Axis.Y;
	const float ZZ = Axis.Z * Axis.Z;

	const float XY = Axis.X * Axis.Y;
	const float YZ = Axis.Y * Axis.Z;
	const float ZX = Axis.Z * Axis.X;

	const float XS = Axis.X * S;
	const float YS = Axis.Y * S;
	const float ZS = Axis.Z * S;

	const float OMC = 1.f - C;

	return FVector(
		(OMC * XX + C) * X + (OMC * XY - ZS) * Y + (OMC * ZX + YS) * Z,
		(OMC * XY + ZS) * X + (OMC * YY + C) * Y + (OMC * YZ - XS) * Z,
		(OMC * ZX - YS) * X + (OMC * YZ + XS) * Y + (OMC * ZZ + C) * Z
	);
}