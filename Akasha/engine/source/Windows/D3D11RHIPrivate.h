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

	// device
	virtual FSamplerStateRHIRef RHICreateSamplerState(const FSamplerStateInitializerRHI& Initializer) final override;
	virtual FRasterizerStateRHIRef RHICreateRasterizerState(const FRasterizerStateInitializerRHI& Initializer) final override;
	virtual FDepthStencilStateRHIRef RHICreateDepthStencilState(const FDepthStencilStateInitializerRHI& Initializer) final override;
	virtual FBlendStateRHIRef RHICreateBlendState(const FBlendStateInitializerRHI& Initializer) final override;
	virtual FVertexDeclarationRHIRef RHICreateVertexDeclaration(const FVertexDeclarationElementList& Elements) final override;
	virtual FPixelShaderRHIRef RHICreatePixelShader(const std::vector<uint8>& Code) final override;
	virtual FVertexShaderRHIRef RHICreateVertexShader(const std::vector<uint8>& Code) final override;
	virtual FHullShaderRHIRef RHICreateHullShader(const std::vector<uint8>& Code) final override;
	virtual FDomainShaderRHIRef RHICreateDomainShader(const std::vector<uint8>& Code) final override;
	virtual FGeometryShaderRHIRef RHICreateGeometryShader(const std::vector<uint8>& Code) final override;
	virtual FBoundShaderStateRHIRef RHICreateBoundShaderState(FVertexDeclarationRHIParamRef VertexDeclaration, FVertexShaderRHIParamRef VertexShader, FHullShaderRHIParamRef HullShader, FDomainShaderRHIParamRef DomainShader, FPixelShaderRHIParamRef PixelShader, FGeometryShaderRHIParamRef GeometryShader) final override;
	virtual FUniformBufferRHIRef RHICreateUniformBuffer(const void* Contents, const FRHIUniformBufferLayout& Layout, EUniformBufferUsage Usage) final override;
	virtual FIndexBufferRHIRef RHICreateIndexBuffer(uint32 Stride, uint32 Size, uint32 InUsage, FRHIResourceCreateInfo& CreateInfo) final override;
	virtual void* RHILockIndexBuffer(FIndexBufferRHIParamRef IndexBuffer, uint32 Offset, uint32 Size, EResourceLockMode LockMode) final override;
	virtual void RHIUnlockIndexBuffer(FIndexBufferRHIParamRef IndexBuffer) final override;
	virtual FVertexBufferRHIRef RHICreateVertexBuffer(uint32 Size, uint32 InUsage, FRHIResourceCreateInfo& CreateInfo) final override;
	virtual void* RHILockVertexBuffer(FVertexBufferRHIParamRef VertexBuffer, uint32 Offset, uint32 SizeRHI, EResourceLockMode LockMode) final override;
	virtual void RHIUnlockVertexBuffer(FVertexBufferRHIParamRef VertexBuffer) final override;
	virtual void RHICopyVertexBuffer(FVertexBufferRHIParamRef SourceBuffer, FVertexBufferRHIParamRef DestBuffer) final override;
	virtual FTexture2DRHIRef RHICreateTexture2D(uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, uint32 NumSamples, uint32 Flags, FRHIResourceCreateInfo& CreateInfo) final override;
	virtual FShaderResourceViewRHIRef RHICreateShaderResourceView(FTexture2DRHIParamRef Texture2DRHI, uint8 MipLevel) final override;
	virtual FShaderResourceViewRHIRef RHICreateShaderResourceView(FTexture2DRHIParamRef Texture2DRHI, uint8 MipLevel, uint8 NumMipLevels, uint8 Format) final override;
	virtual FShaderResourceViewRHIRef RHICreateShaderResourceView(FTextureCubeRHIParamRef TextureCubeRHI, uint8 MipLevel) final override;
	virtual void RHIGenerateMips(FTextureRHIParamRef Texture) final override;
	virtual FTexture2DRHIRef RHIGetViewportBackBuffer(FViewportRHIParamRef Viewport) final override;
	virtual FViewportRHIRef RHICreateViewport(void* WindowHandle, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PreferredPixelFormat) final override;
	virtual void RHIResizeViewport(FViewportRHIParamRef Viewport, uint32 SizeX, uint32 SizeY, bool bIsFullscreen) final override;
	virtual void RHIExecuteCommandList(FRHICommandList* CmdList) final override;
	virtual void* RHIGetNativeDevice() final override;
	virtual class IRHICommandContext* RHIGetDefaultContext() final override;

	// context
	virtual void RHIBeginDrawingViewport(FViewportRHIParamRef Viewport, FTextureRHIParamRef RenderTargetRHI) final override;
	virtual void RHIEndDrawingViewport(FViewportRHIParamRef Viewport, bool bPresent, bool bLockToVsync) final override;
	virtual void RHIBeginFrame() final override;
	virtual void RHIEndFrame() final override;
	virtual void RHIBeginScene() final override;
	virtual void RHIEndScene() final override;
	virtual void RHISetRasterizerState(FRasterizerStateRHIParamRef NewState) final override;
	virtual void RHISetViewport(uint32 MinX, uint32 MinY, float MinZ, uint32 MaxX, uint32 MaxY, float MaxZ) final override;
	virtual void RHISetScissorRect(bool bEnable, uint32 MinX, uint32 MinY, uint32 MaxX, uint32 MaxY) final override;
	virtual void RHISetBoundShaderState(FBoundShaderStateRHIParamRef BoundShaderState) final override;
	virtual void RHISetGraphicsPipelineState(FGraphicsPipelineStateRHIParamRef GraphicsState) final override;
	virtual void RHISetShaderTexture(FVertexShaderRHIParamRef VertexShader, uint32 TextureIndex, FTextureRHIParamRef NewTexture) final override;
	virtual void RHISetShaderTexture(FHullShaderRHIParamRef HullShader, uint32 TextureIndex, FTextureRHIParamRef NewTexture) final override;
	virtual void RHISetShaderTexture(FDomainShaderRHIParamRef DomainShader, uint32 TextureIndex, FTextureRHIParamRef NewTexture) final override;
	virtual void RHISetShaderTexture(FGeometryShaderRHIParamRef GeometryShader, uint32 TextureIndex, FTextureRHIParamRef NewTexture) final override;
	virtual void RHISetShaderTexture(FPixelShaderRHIParamRef PixelShader, uint32 TextureIndex, FTextureRHIParamRef NewTexture) final override;
	virtual void RHISetShaderSampler(FVertexShaderRHIParamRef VertexShader, uint32 SamplerIndex, FSamplerStateRHIParamRef NewState) final override;
	virtual void RHISetShaderSampler(FGeometryShaderRHIParamRef GeometryShader, uint32 SamplerIndex, FSamplerStateRHIParamRef NewState) final override;
	virtual void RHISetShaderSampler(FDomainShaderRHIParamRef DomainShader, uint32 SamplerIndex, FSamplerStateRHIParamRef NewState) final override;
	virtual void RHISetShaderSampler(FHullShaderRHIParamRef HullShader, uint32 SamplerIndex, FSamplerStateRHIParamRef NewState) final override;
	virtual void RHISetShaderSampler(FPixelShaderRHIParamRef PixelShader, uint32 SamplerIndex, FSamplerStateRHIParamRef NewState) final override;
	virtual void RHISetShaderResourceViewParameter(FPixelShaderRHIParamRef PixelShader, uint32 SamplerIndex, FShaderResourceViewRHIParamRef SRV) final override;
	virtual void RHISetShaderResourceViewParameter(FVertexShaderRHIParamRef VertexShader, uint32 SamplerIndex, FShaderResourceViewRHIParamRef SRV) final override;
	virtual void RHISetShaderResourceViewParameter(FHullShaderRHIParamRef HullShader, uint32 SamplerIndex, FShaderResourceViewRHIParamRef SRV) final override;
	virtual void RHISetShaderResourceViewParameter(FDomainShaderRHIParamRef DomainShader, uint32 SamplerIndex, FShaderResourceViewRHIParamRef SRV) final override;
	virtual void RHISetShaderResourceViewParameter(FGeometryShaderRHIParamRef GeometryShader, uint32 SamplerIndex, FShaderResourceViewRHIParamRef SRV) final override;
	virtual void RHISetShaderUniformBuffer(FVertexShaderRHIParamRef VertexShader, uint32 BufferIndex, FUniformBufferRHIParamRef Buffer) final override;
	virtual void RHISetShaderUniformBuffer(FHullShaderRHIParamRef HullShader, uint32 BufferIndex, FUniformBufferRHIParamRef Buffer) final override;
	virtual void RHISetShaderUniformBuffer(FDomainShaderRHIParamRef DomainShader, uint32 BufferIndex, FUniformBufferRHIParamRef Buffer) final override;
	virtual void RHISetShaderUniformBuffer(FGeometryShaderRHIParamRef GeometryShader, uint32 BufferIndex, FUniformBufferRHIParamRef Buffer) final override;
	virtual void RHISetShaderUniformBuffer(FPixelShaderRHIParamRef PixelShader, uint32 BufferIndex, FUniformBufferRHIParamRef Buffer) final override;
	virtual void RHISetShaderParameter(FVertexShaderRHIParamRef VertexShader, uint32 BufferIndex, uint32 BaseIndex, uint32 NumBytes, const void* NewValue) final override;
	virtual void RHISetShaderParameter(FPixelShaderRHIParamRef PixelShader, uint32 BufferIndex, uint32 BaseIndex, uint32 NumBytes, const void* NewValue) final override;
	virtual void RHISetShaderParameter(FHullShaderRHIParamRef HullShader, uint32 BufferIndex, uint32 BaseIndex, uint32 NumBytes, const void* NewValue) final override;
	virtual void RHISetShaderParameter(FDomainShaderRHIParamRef DomainShader, uint32 BufferIndex, uint32 BaseIndex, uint32 NumBytes, const void* NewValue) final override;
	virtual void RHISetShaderParameter(FGeometryShaderRHIParamRef GeometryShader, uint32 BufferIndex, uint32 BaseIndex, uint32 NumBytes, const void* NewValue) final override;
	virtual void RHISetStencilRef(uint32 StencilRef) final override;
	virtual void RHISetBlendFactor(const FLinearColor& BlendFactor) final override;
	virtual void RHISetRenderTargets(uint32 NumSimultaneousRenderTargets, const FRHIRenderTargetView* NewRenderTargets, const FRHIDepthRenderTargetView* NewDepthStencilTarget) final override;
	virtual void RHISetRenderTargetsAndClear(const FRHISetRenderTargetsInfo& RenderTargetsInfo) final override;
	virtual void RHIBindClearMRTValues(bool bClearColor, bool bClearDepth, bool bClearStencil) final override;

	virtual void RHIDrawPrimitive(uint32 PrimitiveType, uint32 BaseVertexIndex, uint32 NumPrimitives, uint32 NumInstances) final override;
	virtual void RHIDrawIndexedPrimitive(FIndexBufferRHIParamRef IndexBuffer, uint32 PrimitiveType, int32 BaseVertexIndex, uint32 FirstInstance, uint32 NumVertices, uint32 StartIndex, uint32 NumPrimitives, uint32 NumInstances) final override;
	virtual void RHIDrawIndexedPrimitiveIndirect(uint32 PrimitiveType, FIndexBufferRHIParamRef IndexBuffer, FVertexBufferRHIParamRef ArgumentBuffer, uint32 ArgumentOffset) final override;

	virtual void RHIBeginDrawPrimitiveUP(uint32 PrimitiveType, uint32 NumPrimitives, uint32 NumVertices, uint32 VertexDataStride, void*& OutVertexData) final override; // Ìî³ä¶¯Ì¬vb
	virtual void RHIEndDrawPrimitiveUP() final override;;
	virtual void RHIBeginDrawIndexedPrimitiveUP(uint32 PrimitiveType, uint32 NumPrimitives, uint32 NumVerteics, uint32 VertexDataStride, void*& OutVertexData, uint32 MinVertexIndex, uint32 NumIndices, uint32 IndexDataStride, void*& OutIndexData) final override;;
	virtual void RHIEndDrawIndexedPrimitiveUP() final override;
	virtual void RHIEnableDepthBoundsTest(bool bEnable, float MinDepth, float MaxDepth) final override;

	// Accessors.
	ID3D11Device* GetDevice() const
	{
		return Direct3DDevice.get();
	}
	FD3D11DeviceContext* GetDeviceContext() const
	{
		return Direct3DDeviceIMContext.get();
	}

protected:
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