#pragma once

#include "TypeDefines.h"


/**
* 32 bit float components
*/
class FFloat32
{
public:

	union
	{
		struct
		{
			uint32	Mantissa : 23;
			uint32	Exponent : 8;
			uint32	Sign : 1;			
		} Components;

		float	FloatValue;
	};

	/**
	 * Constructor
	 * 
	 * @param InValue value of the float.
	 */
	FFloat32( float InValue=0.0f );
};


__forceinline FFloat32::FFloat32( float InValue)
	: FloatValue(InValue)
{ }
