#pragma once
#include <windows.h>
#include "TypeDefines.h"
#include "directx/d3d11.h"
/**
* Checks that the given result isn't a failure.  If it is, the application exits with an appropriate error message.
* @param	Result - The result code to check.
* @param	Code - The code which yielded the result.
* @param	Filename - The filename of the source file containing Code.
* @param	Line - The line number of Code within Filename.
*/
extern void VerifyD3D11Result(HRESULT Result, const char* Code, const char* Filename, uint32 Line, ID3D11Device* Device);



#define VERIFYD3D11RESULT_EX(x, Device) {HRESULT hr = x; if (FAILED(hr)) { VerifyD3D11Result(hr,#x,__FILE__,__LINE__, Device); }}
#define VERIFYD3D11RESULT(x)			{HRESULT hr = x; if (FAILED(hr)) { VerifyD3D11Result(hr,#x,__FILE__,__LINE__, 0); }}