#include "stdafx.h"
#include "D3D11Util.h"
#include "CoreDefines.h"
#include <string>

#define D3DERR(x) case x: ErrorCodeText = TEXT(#x); break;

static std::wstring GetD3D11DeviceHungErrorString(HRESULT ErrorCode)
{
	std::wstring ErrorCodeText;

	switch (ErrorCode)
	{
		D3DERR(DXGI_ERROR_DEVICE_HUNG)
			D3DERR(DXGI_ERROR_DEVICE_REMOVED)
			D3DERR(DXGI_ERROR_DEVICE_RESET)
			D3DERR(DXGI_ERROR_DRIVER_INTERNAL_ERROR)
			D3DERR(DXGI_ERROR_INVALID_CALL)
	default: ErrorCodeText = std::wstring(TEXT("%08X"), (int32)ErrorCode);
	}

	return ErrorCodeText;
}

static std::wstring GetD3D11ErrorString(HRESULT ErrorCode, ID3D11Device* Device)
{
	std::wstring ErrorCodeText;

	switch (ErrorCode)
	{
		D3DERR(S_OK);
		D3DERR(D3D11_ERROR_FILE_NOT_FOUND)
			D3DERR(D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS)
			D3DERR(E_FAIL)
			D3DERR(E_INVALIDARG)
			D3DERR(E_OUTOFMEMORY)
			D3DERR(DXGI_ERROR_INVALID_CALL)
			D3DERR(E_NOINTERFACE)
			D3DERR(DXGI_ERROR_DEVICE_REMOVED)
	default: ErrorCodeText = std::wstring(TEXT("%08X"), (int32)ErrorCode);
	}

	if (ErrorCode == DXGI_ERROR_DEVICE_REMOVED && Device)
	{
		HRESULT hResDeviceRemoved = Device->GetDeviceRemovedReason();
		ErrorCodeText += std::wstring(TEXT(" ")) + GetD3D11DeviceHungErrorString(hResDeviceRemoved);
	}

	return ErrorCodeText;
}

void VerifyD3D11Result(HRESULT Result, const char* Code, const char* Filename, uint32 Line, ID3D11Device* Device)
{
	check(FAILED(Result));

	const std::wstring ErrorString = GetD3D11ErrorString(Result, Device);

	char logStr[256] = "";
	sprintf_s(logStr, "%s failed at %s:%u with error %s.\n", Code, Filename, Line, ErrorString.c_str());

	//LOG(FATAL) << logStr;

	exit(0);
}