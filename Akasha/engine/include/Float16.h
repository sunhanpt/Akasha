#pragma once
#include "TypeDefines.h"
#include "Float32.h"
#include "MathUtility.h"
/**
* 16 bit float components and conversion
*
*
* IEEE float 16
* Represented by 10-bit mantissa M, 5-bit exponent E, and 1-bit sign S
*
* Specials:
*
* E=0, M=0			== 0.0
* E=0, M!=0			== Denormalized value (M / 2^10) * 2^-14
* 0<E<31, M=any		== (1 + M / 2^10) * 2^(E-15)
* E=31, M=0			== Infinity
* E=31, M!=0		== NAN
*
*/
class FFloat16
{
public:
	union
	{
		struct
		{
			uint16	Mantissa : 10;
			uint16	Exponent : 5;
			uint16	Sign : 1;
		} Components;

		uint16	Encoded;
	};

	/** Default constructor */
	FFloat16();

	/** Copy constructor. */
	FFloat16(const FFloat16& FP16Value);

	/** Conversion constructor. Convert from Fp32 to Fp16. */
	FFloat16(float FP32Value);

	/** Assignment operator. Convert from Fp32 to Fp16. */
	FFloat16& operator=(float FP32Value);

	/** Assignment operator. Copy Fp16 value. */
	FFloat16& operator=(const FFloat16& FP16Value);

	/** Convert from Fp16 to Fp32. */
	operator float() const;

	/** Convert from Fp32 to Fp16. */
	void Set(float FP32Value);

	/**
	* Convert from Fp32 to Fp16 without doing any checks if
	* the Fp32 exponent is too large or too small. This is a
	* faster alternative to Set() when you know the values
	* within the single precision float don't need the checks.
	*
	* @param FP32Value Single precision float to be set as half precision.
	*/
	void SetWithoutBoundsChecks(const float FP32Value);

	/** Convert from Fp16 to Fp32. */
	float GetFloat() const;
};


__forceinline FFloat16::FFloat16()
	: Encoded(0)
{ }


__forceinline FFloat16::FFloat16(const FFloat16& FP16Value)
{
	Encoded = FP16Value.Encoded;
}


__forceinline FFloat16::FFloat16(float FP32Value)
{
	Set(FP32Value);
}


__forceinline FFloat16& FFloat16::operator=(float FP32Value)
{
	Set(FP32Value);
	return *this;
}


__forceinline FFloat16& FFloat16::operator=(const FFloat16& FP16Value)
{
	Encoded = FP16Value.Encoded;
	return *this;
}


__forceinline FFloat16::operator float() const
{
	return GetFloat();
}


__forceinline void FFloat16::Set(float FP32Value)
{
	FFloat32 FP32(FP32Value);

	// Copy sign-bit
	Components.Sign = FP32.Components.Sign;

	// Check for zero, denormal or too small value.
	if (FP32.Components.Exponent <= 112)			// Too small exponent? (0+127-15)
	{
		// Set to 0.
		Components.Exponent = 0;
		Components.Mantissa = 0;
	}
	// Check for INF or NaN, or too high value
	else if (FP32.Components.Exponent >= 143)		// Too large exponent? (31+127-15)
	{
		// Set to 65504.0 (max value)
		Components.Exponent = 30;
		Components.Mantissa = 1023;
	}
	// Handle normal number.
	else
	{
		Components.Exponent = int32(FP32.Components.Exponent) - 127 + 15;
		Components.Mantissa = uint16(FP32.Components.Mantissa >> 13);
	}
}


__forceinline void FFloat16::SetWithoutBoundsChecks(const float FP32Value)
{
	const FFloat32 FP32(FP32Value);

	// Make absolutely sure that you never pass in a single precision floating
	// point value that may actually need the checks. If you are not 100% sure
	// of that just use Set().

	Components.Sign = FP32.Components.Sign;
	Components.Exponent = int32(FP32.Components.Exponent) - 127 + 15;
	Components.Mantissa = uint16(FP32.Components.Mantissa >> 13);
}


__forceinline float FFloat16::GetFloat() const
{
	FFloat32	Result;

	Result.Components.Sign = Components.Sign;
	if (Components.Exponent == 0)
	{
		uint32 Mantissa = Components.Mantissa;
		if (Mantissa == 0)
		{
			// Zero.
			Result.Components.Exponent = 0;
			Result.Components.Mantissa = 0;
		}
		else
		{
			// Denormal.
			uint32 MantissaShift = 10 - (uint32)FMath::TruncToInt(FMath::Log2(Mantissa));
			Result.Components.Exponent = 127 - (15 - 1) - MantissaShift;
			Result.Components.Mantissa = Mantissa << (MantissaShift + 23 - 10);
		}
	}
	else if (Components.Exponent == 31)		// 2^5 - 1
	{
		// Infinity or NaN. Set to 65504.0
		Result.Components.Exponent = 142;
		Result.Components.Mantissa = 8380416;
	}
	else
	{
		// Normal number.
		Result.Components.Exponent = int32(Components.Exponent) - 15 + 127; // Stored exponents are biased by half their range.
		Result.Components.Mantissa = uint32(Components.Mantissa) << 13;
	}

	return Result.FloatValue;
}
