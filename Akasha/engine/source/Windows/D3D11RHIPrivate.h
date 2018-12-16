#pragma once

#include "DynamicRHI.h"
#include "directx/D3Dcommon.h"
#include "directx/DXGI.h"
#include "directx/D3D11.h"
#include "RHIContext.h"
#include "RHIResources.h"
#include "D3D11ConstantBuffer.h"
#include <memory>
#include <vector>

typedef ID3D11DeviceContext FD3D11DeviceContext;
typedef ID3D11Device FD3D11Device;

class FD3D11Viewport;
class FD3D11TextureBase;

class FD3D11DynamicRHI : public FDynamicRHI, public IRHICommandContext
{
public:
	friend class FD3D11Viewport;

	FD3D11DynamicRHI(D3D_FEATURE_LEVEL InFeatureLevel);

	virtual ~FD3D11DynamicRHI();

	virtual void InitD3DDevice();

	virtual void Init() override;
	virtual void ShutDown() override; 
	virtual const TCHAR* GetName() override { return TEXT("D3D11"); }

	// HDR
	virtual void EnableHDR();
	virtual void ShutdownHDR();

//private:
	//////////////////////////////////////////////////////////////////////////
	D3D_FEATURE_LEVEL						FeatureLevel;

	std::shared_ptr<FD3D11Device>			Direct3DDevice;
	std::shared_ptr<FD3D11DeviceContext>	Direct3DDeviceIMContext;

	std::vector<FD3D11Viewport*>			Viewports;					// A list of all viewport RHIs that have been created.
	std::shared_ptr<FD3D11Viewport>			DrawingViewport;			// The viewport which is currently being drawn.

	std::shared_ptr<ID3D11RenderTargetView>	CurrentRenderTargets[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]; 
	std::shared_ptr<ID3D11DepthStencilView> CurrentDepthStencilTarget;
	std::shared_ptr<FD3D11TextureBase>		CurrentDepthTexture;

	uint32									SceneFrameCounster;			// Internal frame counter, incremented on each call to RHIBeginScene.
	uint32									PresentCounter;				// Internal frame counter that just counts calls to Present

	enum { MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE = 14 };					// D3D11 defines a maximum of 14 constant buffers per shader stage.
	FUniformBufferRHIRef					BoundUniformBuffers[SF_NumFrequencies][MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE];

	// Bit array to track which uniform buffers have changed since the last draw call.
	uint16									DirtyUniformBuffers[SF_NumFrequencies];

	FExclusiveDepthStencil					CurrentDSVAccessType;

	/** When a new shader is set, we discard all old constants set for the previous shader. */
	bool bDiscardSharedConstants;

	/** Set to true when the current shading setup uses tessellation */
	bool bUsingTessellation;

	//std::shared_ptr<FD3D11DynamicBuffer> DynamicVB; // ´ýÌí¼Ódynamic buffer
	//std::shared_ptr<FD3D11DynamicBuffer> DynamicIB;

	std::vector<std::shared_ptr<FD3D11ConstantBuffer>>	VSConstantBuffers;
	std::vector<std::shared_ptr<FD3D11ConstantBuffer>>	HSConstantBuffers;
	std::vector<std::shared_ptr<FD3D11ConstantBuffer>>	DSConstantBuffers;
	std::vector<std::shared_ptr<FD3D11ConstantBuffer>>	PSConstantBuffers;
	std::vector<std::shared_ptr<FD3D11ConstantBuffer>>	GSConstantBuffers;

	/** Initializes the constant buffers.  Called once at RHI initialization time. */
	void InitConstantBuffers();

	/**
	* Cleanup the D3D device.
	* This function must be called from the main game thread.
	*/
	virtual void CleanupD3DDevice();

	void ReleasePooledUniformBuffers();
};

class FD3D11DynamicRHIModule : public IDynamicRHIModule
{
public:
	virtual void StartupModule() override;
	virtual FDynamicRHI* CreateRHI(ERHIFeatureLevel::Type RequestedFeatureLevel = ERHIFeatureLevel::Num) override;
};

/** Find an appropriate DXGI format for the input format and SRGB setting. */
inline DXGI_FORMAT FindShaderResourceDXGIFormat(DXGI_FORMAT InFormat, bool bSRGB)
{
	if (bSRGB)
	{
		switch (InFormat)
		{
		case DXGI_FORMAT_B8G8R8A8_TYPELESS:	return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		case DXGI_FORMAT_R8G8B8A8_TYPELESS: return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		case DXGI_FORMAT_BC1_TYPELESS:		return DXGI_FORMAT_BC1_UNORM_SRGB;
		case DXGI_FORMAT_BC2_TYPELESS:		return DXGI_FORMAT_BC2_UNORM_SRGB;
		case DXGI_FORMAT_BC3_TYPELESS:		return DXGI_FORMAT_BC3_UNORM_SRGB;
		case DXGI_FORMAT_BC7_TYPELESS:		return DXGI_FORMAT_BC7_UNORM_SRGB;
		}
	}
	else
	{
		switch (InFormat)
		{
		case DXGI_FORMAT_B8G8R8A8_TYPELESS: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case DXGI_FORMAT_R8G8B8A8_TYPELESS: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case DXGI_FORMAT_BC1_TYPELESS:      return DXGI_FORMAT_BC1_UNORM;
		case DXGI_FORMAT_BC2_TYPELESS:      return DXGI_FORMAT_BC2_UNORM;
		case DXGI_FORMAT_BC3_TYPELESS:      return DXGI_FORMAT_BC3_UNORM;
		case DXGI_FORMAT_BC7_TYPELESS:      return DXGI_FORMAT_BC7_UNORM;
		};
	}

	switch (InFormat)
	{
	case DXGI_FORMAT_R24G8_TYPELESS:	return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	case DXGI_FORMAT_R32_TYPELESS:		return DXGI_FORMAT_R32_FLOAT;
	case DXGI_FORMAT_R16_TYPELESS:		return DXGI_FORMAT_R16_UNORM;
	}

	return InFormat;
}

/** Find the appropriate depth-stencil targetable DXGI format for the given format. */
inline DXGI_FORMAT FindDepthStencilDXGIFormat(DXGI_FORMAT InFormat)
{
	switch (InFormat)
	{
	case DXGI_FORMAT_R24G8_TYPELESS:	return DXGI_FORMAT_D24_UNORM_S8_UINT;
	case DXGI_FORMAT_R32_TYPELESS:		return DXGI_FORMAT_D32_FLOAT;
	case DXGI_FORMAT_R16_TYPELESS:		return DXGI_FORMAT_R16_FLOAT;
	}
	return InFormat;
}

/**
* Returns whether the given format contains stencil information.
* Must be passed a format returned by FindDepthStencilDXGIFormat, so that typeless versions are converted to their corresponding depth stencil view format.
*/
inline bool HasStencilBits(DXGI_FORMAT InFormat)
{
	switch (InFormat)
	{
	case DXGI_FORMAT_D24_UNORM_S8_UINT:		return true;
	}

	return false;
}