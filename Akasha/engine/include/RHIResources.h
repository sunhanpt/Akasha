#pragma once

#include "TypeDefines.h"
#include "CoreDefines.h"
#include "taskGraph/ThreadSafeCounter.h"
#include <cassert>
#include "ThreadSafeStack.h"
#include "Hash.h"
#include "PixelFormat.h"
#include "RHI.h"
#include <memory>
#include "AlignmentTemplates.h"
#include "RHIDefines.h"

class AKADLL_API FRHIResource
{
public:
	FRHIResource(bool InbDoNotDeferDelte = false)
		: m_MarkedForDelete(0)
		, m_bDoNotDeferDelete(InbDoNotDeferDelte)
		, m_bCommitted(false)
	{
	}

	virtual ~FRHIResource()
	{
		assert(m_NumRefs.GetValue() == 0);
	}

	__forceinline uint32 AddRef() const 
	{
		int32 NewValue = m_NumRefs.Increment();
		assert(NewValue > 0);
		return uint32(NewValue);
	}

	__forceinline uint32 Release() const
	{
		int32 NewValue = m_NumRefs.Decrement();
		if (NewValue == 0)
		{
			if (!DeferDelete())
			{
				delete this;
			}
			else
			{
				if (_InterlockedCompareExchange(&m_MarkedForDelete, 1, 0) == 0) // 保证此resouce只被放到pending中一次。
				{
					s_PendingDeletes.Push(const_cast<FRHIResource*>(this));
				}
			}
		}

		assert(NewValue >= 0);
		return uint32(NewValue);
	}

	__forceinline uint32 GetRefCount() const
	{
		int32 CurrentValue = m_NumRefs.GetValue();
		assert(CurrentValue >= 0);
		return uint32(CurrentValue);
	}

	void DoNoDeferDelete()
	{
		assert(!m_MarkedForDelete); // 没被排队删除
		m_bDoNotDeferDelete = true;
	}

	void SetCommitted(bool bInCommitted)
	{
		// 应该在render线程调用
		m_bCommitted = bInCommitted;
	}

	bool IsCommitted() const
	{
		// 应该在render线程调用
		return m_bCommitted;
	}

	static void FlushPendingDeltes();

private:
	mutable FThreadSafeCounter	m_NumRefs;
	mutable	int32				m_MarkedForDelete;
	bool						m_bDoNotDeferDelete;
	bool						m_bCommitted;

	static FThreadSafeStack<FRHIResource*>	s_PendingDeletes;
	static FRHIResource*					s_CurrentlyDeleting;

	__forceinline bool DeferDelete() const
	{
		return !m_bDoNotDeferDelete; // TODO: Add other conditions.
	}
};

// state block
class FRHISamplerState : public FRHIResource {};
class FRHIRasterizerState : public FRHIResource {};
class FRHIDepthStencilState : public FRHIResource {};
class FRHIBlendState : public FRHIResource {};

// shader binding
class FRHIVertexDeclaration : public FRHIResource {};
class FRHIBoundShaderState : public FRHIResource {};


class FRHIShader : public FRHIResource
{
public:
	FRHIShader(bool InbDoNotDeferDelete = false) : FRHIResource(InbDoNotDeferDelete) {}

#if _DEBUG
	std::string m_ShaderName;
#endif

private:
	AHash m_Hash;
};


class FRHIVertexShader : public FRHIResource {};
class FRHIHullShader : public FRHIResource {};
class FRHIDomainShader : public FRHIResource {};
class FRHIPixelShader : public FRHIResource {};
class FRHIGeometryShader : public FRHIResource {};
class FRHIComputerShader : public FRHIResource {};

class FRHIGraphicsPipelineState : public FRHIResource {};

// Buffer
/** The layout of a uniform buffer in memory. */
struct FRHIUniformBufferLayout
{
	/** The size of the constant buffer in bytes. */
	uint32 ConstantBufferSize;
	/** The offset to the beginning of the resource table. */
	uint32 ResourceOffset;
	/** The type of each resource (EUniformBufferBaseType). */
	std::vector<uint8> Resources;

	uint32 GetHash() const
	{
		if (!bComputedHash)
		{
			uint32 TmpHash = ConstantBufferSize << 16;
			// This is to account for 32vs64 bits difference in pointer sizes.
			TmpHash ^= Align(ResourceOffset, 8);
			uint32 N = (uint32)Resources.size();
			while (N >= 4)
			{
				TmpHash ^= (Resources[--N] << 0);
				TmpHash ^= (Resources[--N] << 8);
				TmpHash ^= (Resources[--N] << 16);
				TmpHash ^= (Resources[--N] << 24);
			}
			while (N >= 2)
			{
				TmpHash ^= Resources[--N] << 0;
				TmpHash ^= Resources[--N] << 16;
			}
			while (N > 0)
			{
				TmpHash ^= Resources[--N];
			}
			Hash = TmpHash;
			bComputedHash = true;
		}
		return Hash;
	}

	explicit FRHIUniformBufferLayout(std::string& InName) :
		ConstantBufferSize(0),
		ResourceOffset(0),
		Name(InName),
		Hash(0),
		bComputedHash(false)
	{
	}

	enum EInit
	{
		Zero
	};
	explicit FRHIUniformBufferLayout(EInit) :
		ConstantBufferSize(0),
		ResourceOffset(0),
		Name(""),
		Hash(0),
		bComputedHash(false)
	{
	}

	void CopyFrom(const FRHIUniformBufferLayout& Source)
	{
		ConstantBufferSize = Source.ConstantBufferSize;
		ResourceOffset = Source.ResourceOffset;
		Resources = Source.Resources;
		Name = Source.Name;
		Hash = Source.Hash;
		bComputedHash = Source.bComputedHash;
	}

	const std::string GetDebugName() const { return Name; }

private:
	// for debugging / error message
	std::string Name;

	mutable uint32 Hash;
	mutable bool bComputedHash;
};


/** Compare two uniform buffer layouts. */
inline bool operator==(const FRHIUniformBufferLayout& A, const FRHIUniformBufferLayout& B)
{
	return A.ConstantBufferSize == B.ConstantBufferSize
		&& A.ResourceOffset == B.ResourceOffset
		&& A.Resources == B.Resources;
}

class FRHIUniformBuffer : public FRHIResource
{
public:

	/** Initialization constructor. */
	FRHIUniformBuffer(const FRHIUniformBufferLayout& InLayout)
		: Layout(&InLayout)
	{}

	/** @return The number of bytes in the uniform buffer. */
	uint32 GetSize() const { return Layout->ConstantBufferSize; }
	const FRHIUniformBufferLayout& GetLayout() const { return *Layout; }

private:
	/** Layout of the uniform buffer. */
	const FRHIUniformBufferLayout* Layout;
};


class FRHIIndexBuffer : public FRHIResource
{
public:
	FRHIIndexBuffer(uint32 InStride, uint32 InSize, uint32 InUsage)
		: m_Stride(InStride)
		, m_Size(InSize)
		, m_Usage(InUsage)
	{
	}

	uint32 GetStride() const { return m_Stride; }
	uint32 GetSize() const { return m_Size; }
	uint32 GetUsage() const { return m_Usage; }

private:
	uint32 m_Stride;
	uint32 m_Size;
	uint32 m_Usage;
};

class FRHIVertexBuffer : public FRHIResource
{
public:
	FRHIVertexBuffer(uint32 InSize, uint32 InUsage)
		: m_Size(InSize)
		, m_Usage(InUsage)
	{}
private:
	uint32 m_Size;
	uint32 m_Usage;
};

class FRHITexture : public FRHIResource
{
public:
	FRHITexture(uint32 InNumMips, uint32 InNumSamples, EPixelFormat InFormat, uint32 InFlags, const FClearValueBinding& InClearValue)
		: m_ClearValue(InClearValue)
		, m_NumMips(InNumMips)
		, m_NumSamples(InNumMips)
		, m_Format(InFormat)
		, m_Flags(InFlags)
	{}

	virtual class FRHITexture2D* GetTexture2D() { return nullptr; }
	virtual class FRHITexture2DArray* GetTexture2DArray() { return nullptr; }
	virtual class FRHITexture3D* GetTexture3D() { return nullptr; }
	virtual class FRHITextureCube* GetTextureCube() { return nullptr; }
	virtual class FRHITextureReference* GetTextureReference() { return nullptr; }

	virtual void* GetNativeResource() const { return nullptr; }
	virtual void* GetNativeShaderResourceView() const { return nullptr; }

	uint32 GetNumMips() const { return m_NumMips; }
	EPixelFormat GetFormat() const { return m_Format; }
	uint32 GetFlags() const { return m_Flags; }
	uint32 GetNumSamples() const { return m_NumSamples; }
	bool IsMultiSampled() const { return m_NumSamples > 1; }
	void SetName(const std::string& Name) { m_TextureName = Name; }
	const std::string& GetName() { return m_TextureName; }

	bool HasClearValue() const
	{
		return m_ClearValue.ColorBinding != EClearBinding::ENoneBound;
	}

	FLinearColor GetClearColor() const
	{
		return m_ClearValue.GetClearColor();
	}

	void GetDepthStencilClearValue(float& OutDepth, uint32& OutStencil) const
	{
		return m_ClearValue.GetDepthStencil(OutDepth, OutStencil);
	}

	float GetDepthClearValue() const
	{
		float Depth;
		uint32 Stencil;
		m_ClearValue.GetDepthStencil(Depth, Stencil);
		return Depth;
	}

	uint32 GetStencilClearValue() const
	{
		float Depth;
		uint32 Stencil;
		m_ClearValue.GetDepthStencil(Depth, Stencil);
		return Stencil;
	}

	const FClearValueBinding GetClearBinding() const
	{
		return m_ClearValue;
	}

private:
	FClearValueBinding m_ClearValue;
	uint32 m_NumMips;
	uint32 m_NumSamples;
	EPixelFormat m_Format;
	uint32 m_Flags;
	std::string m_TextureName;
};

class FRHITexture2D : public FRHITexture
{
public:
	FRHITexture2D(uint32 InSizeX, uint32 InSizeY, uint32 InNumMips, uint32 InNumSamples, EPixelFormat InFormat, uint32 InFlags, const FClearValueBinding& InClearValue)
		: FRHITexture(InNumMips, InNumSamples, InFormat, InFlags, InClearValue)
		, m_SizeX(InSizeX)
		, m_SizeY(InSizeY)
	{}

	virtual FRHITexture2D* GetTexture2D() { return this; }

	uint32 GetSizeX() const { return m_SizeX; }
	uint32 GetSizeY() const { return m_SizeY; }

private:
	uint32 m_SizeX;
	uint32 m_SizeY;
};

class FRHITextureCube : public FRHITexture
{
public:
	FRHITextureCube(uint32 InSize, uint32 InNumMips, EPixelFormat InFormat, uint32 InFlags, const FClearValueBinding& InClearValue)
		: FRHITexture(InNumMips, 1, InFormat, InFlags, InClearValue)
		, m_Size(InSize)
	{}

	virtual FRHITextureCube* GetTextureCube() { return this; }

	uint32 GetSize() const { return m_Size; }

private:
	uint32 m_Size;
};

class FRHITextureReference : public FRHITexture
{
public:
	explicit FRHITextureReference()
		: FRHITexture(0, 0, PF_Unknown, 0, FClearValueBinding())
	{}

	virtual FRHITextureReference* GetTextureReference() override { return this; }
	inline FRHITexture* GetReferencedTexture() const { return m_ReferencedTexture.get(); }

	void SetReferencedTexture(FRHITexture* InTexture) { m_ReferencedTexture = std::shared_ptr<FRHITexture>(InTexture); }

private:
	std::shared_ptr<FRHITexture> m_ReferencedTexture;
};

class FRHICustomPresent;
class FRHIViewport : public FRHIResource
{
public:
	FRHIViewport() : FRHIResource(true) {}

	virtual void* GetNativeSwapChain() const { return nullptr; }
	virtual void* GetNativeBackBufferTexture() const { return nullptr; }
	virtual void* GetNativeBackBufferRT() const { return nullptr; }
	virtual void* GetNativeWindow(void** AddParam = nullptr) const { return nullptr; }
	virtual void SetCustomPresent(FRHICustomPresent* InPresent) {}
	virtual FRHICustomPresent* GetCustomPresent() const { return nullptr; }
};


class FRHIShaderResourceView : public FRHIResource {};

typedef FRHISamplerState*						FSamplerStateRHIParamRef;
typedef std::shared_ptr<FRHISamplerState>		FSamplerStateRHIRef;

typedef FRHIRasterizerState*					FRasterizerStateRHIParamRef;
typedef std::shared_ptr<FRHIRasterizerState>	FRasterizerStateRHIRef;

typedef FRHIDepthStencilState*					FDepthStencilStateRHIParamRef;
typedef std::shared_ptr<FRHIDepthStencilState>	FDepthStencilStateRHIRef;

typedef FRHIBlendState*							FBlendStateRHIParamRef;
typedef std::shared_ptr<FRHIBlendState>			FBlendStateRHIRef;

typedef FRHIVertexDeclaration*					FVertexDeclarationRHIParamRef;
typedef std::shared_ptr<FRHIVertexDeclaration>	FVertexDeclarationRHIef;

typedef FRHIBoundShaderState*					FBoundShaderStateRHIParamRef;
typedef std::shared_ptr<FRHIBoundShaderState>	FBoundShaderStateRHIRef;

typedef FRHIVertexShader*						FVertexShaderRHIParamRef;
typedef std::shared_ptr<FRHIVertexShader>		FVertexShaderRHIRef;

typedef FRHIHullShader*							FHullShaderRHIParamRef;
typedef std::shared_ptr<FRHIHullShader>			FHullShaderRHIRef;

typedef FRHIDomainShader*						FDomainShaderRHIParamRef;
typedef std::shared_ptr<FRHIDomainShader>		FDomainShaderRHIRef;

typedef FRHIGeometryShader*						FGeometryShaderRHIParamRef;
typedef std::shared_ptr<FRHIGeometryShader>		FGeometryShaderRHIRef;

typedef FRHIPixelShader*						FPixelShaderRHIParamRef;
typedef std::shared_ptr<FRHIPixelShader>		FPixelShaderRHIRef;

typedef FRHIUniformBuffer*						FUniformBufferRHIParamRef;
typedef std::shared_ptr<FRHIUniformBuffer>		FUniformBufferRHIRef;

typedef FRHITexture*							FTextureRHIParamRef;
typedef std::shared_ptr<FRHITexture>			FTextureRHIRef;

typedef FRHITexture2D*							FTexture2DRHIParamRef;
typedef std::shared_ptr<FRHITexture2D>			FTexture2DRHIRef;

typedef FRHITextureCube*						FTextureCubeRHIParamRef;
typedef std::shared_ptr<FRHITextureCube>		FTextureCubeRHIRef;

typedef FRHITextureReference*					FTextureReferenceRHIParamRef;
typedef std::shared_ptr<FRHITextureReference>	FTextureReferenceRHIRef;

typedef FRHIViewport*							FViewportRHIParamRef;
typedef std::shared_ptr<FRHIViewport>			FViewportRHIRef;

typedef FRHIShaderResourceView*							FShaderResourceViewRHIParamRef;
typedef std::shared_ptr<FRHIShaderResourceView>			FShaderResourceViewRHIRef;

typedef FRHIGraphicsPipelineState*						FGraphicsPipelineStateRHIParamRef;
typedef std::shared_ptr<FRHIGraphicsPipelineState>		FGraphicsPipelineStateRHIRef;

class FRHIRenderTargetView
{
public:
	FTextureRHIParamRef			Texture;
	uint32						MipIndex;
	uint32						ArraySliceIndex;
	ERenderTargetLoadAction		LoadAction;
	ERenderTargetStoreAction	StoreAction;

	FRHIRenderTargetView()
		: Texture(nullptr)
		, MipIndex(0)
		, ArraySliceIndex(-1)
		, LoadAction(ERenderTargetLoadAction::ENoAction)
		, StoreAction(ERenderTargetStoreAction::ENoAction)
	{}

	FRHIRenderTargetView(const FRHIRenderTargetView& Other)
		: Texture(Other.Texture)
		, MipIndex(Other.MipIndex)
		, ArraySliceIndex(Other.ArraySliceIndex)
		, LoadAction(Other.LoadAction)
		, StoreAction(Other.StoreAction)
	{}

	explicit FRHIRenderTargetView(FTextureRHIParamRef InTexture, ERenderTargetLoadAction InLoadAction)
		: Texture(InTexture)
		, MipIndex(0)
		, ArraySliceIndex(-1)
		, LoadAction(InLoadAction)
		, StoreAction(ERenderTargetStoreAction::EStore)
	{}

	explicit FRHIRenderTargetView(FTextureRHIParamRef InTexture, ERenderTargetLoadAction InLoadAction, uint32 InMipIndex, uint32 InArraySliceIndex)
		: Texture(InTexture)
		, LoadAction(InLoadAction)
		, MipIndex(InMipIndex)
		, ArraySliceIndex(InArraySliceIndex)
	{}

	explicit FRHIRenderTargetView(FTextureRHIParamRef InTexture, uint32 InMipIndex, uint32 InArraySliceIndex, ERenderTargetLoadAction InLoadAction, ERenderTargetStoreAction InStoreAction)
		: Texture(InTexture)
		, MipIndex(InMipIndex)
		, ArraySliceIndex(InArraySliceIndex)
		, LoadAction(InLoadAction)
		, StoreAction(InStoreAction)
	{}

	bool operator==(const FRHIRenderTargetView& Other) const
	{
		return
			Texture == Other.Texture &&
			MipIndex == Other.MipIndex &&
			ArraySliceIndex == Other.ArraySliceIndex &&
			LoadAction == Other.LoadAction &&
			StoreAction == Other.StoreAction;
	}
};

class FExclusiveDepthStencil
{
public:
	enum Type
	{
		// don't use those directly, use the combined versions below
		// 4 bits are used for depth and 4 for stencil to make the hex value readable and non overlapping
		DepthNop = 0x00,
		DepthRead = 0x01,
		DepthWrite = 0x02,
		DepthMask = 0x0f,
		StencilNop = 0x00,
		StencilRead = 0x10,
		StencilWrite = 0x20,
		StencilMask = 0xf0,

		// use those:
		DepthNop_StencilNop = DepthNop + StencilNop,
		DepthRead_StencilNop = DepthRead + StencilNop,
		DepthWrite_StencilNop = DepthWrite + StencilNop,
		DepthNop_StencilRead = DepthNop + StencilRead,
		DepthRead_StencilRead = DepthRead + StencilRead,
		DepthWrite_StencilRead = DepthWrite + StencilRead,
		DepthNop_StencilWrite = DepthNop + StencilWrite,
		DepthRead_StencilWrite = DepthRead + StencilWrite,
		DepthWrite_StencilWrite = DepthWrite + StencilWrite,
	};

private:
	Type Value;

public:
	// constructor
	FExclusiveDepthStencil(Type InValue = DepthNop_StencilNop)
		: Value(InValue)
	{
	}

	inline bool IsUsingDepthStencil() const
	{
		return Value != DepthNop_StencilNop;
	}
	inline bool IsUsingDepth() const
	{
		return (ExtractDepth() != DepthNop);
	}
	inline bool IsUsingStencil() const
	{
		return (ExtractStencil() != StencilNop);
	}
	inline bool IsDepthWrite() const
	{
		return ExtractDepth() == DepthWrite;
	}
	inline bool IsStencilWrite() const
	{
		return ExtractStencil() == StencilWrite;
	}

	inline bool IsAnyWrite() const
	{
		return IsDepthWrite() || IsStencilWrite();
	}

	inline void SetDepthWrite()
	{
		Value = (Type)(ExtractStencil() | DepthWrite);
	}
	inline void SetStencilWrite()
	{
		Value = (Type)(ExtractDepth() | StencilWrite);
	}
	inline void SetDepthStencilWrite(bool bDepth, bool bStencil)
	{
		Value = DepthNop_StencilNop;

		if (bDepth)
		{
			SetDepthWrite();
		}
		if (bStencil)
		{
			SetStencilWrite();
		}
	}
	bool operator==(const FExclusiveDepthStencil& rhs) const
	{
		return Value == rhs.Value;
	}
	inline bool IsValid(FExclusiveDepthStencil& Current) const
	{
		Type Depth = ExtractDepth();

		if (Depth != DepthNop && Depth != Current.ExtractDepth())
		{
			return false;
		}

		Type Stencil = ExtractStencil();

		if (Stencil != StencilNop && Stencil != Current.ExtractStencil())
		{
			return false;
		}

		return true;
	}

	uint32 GetIndex() const
	{
		// Note: The array to index has views created in that specific order.

		// we don't care about the Nop versions so less views are needed
		// we combine Nop and Write
		switch (Value)
		{
		case DepthWrite_StencilNop:
		case DepthNop_StencilWrite:
		case DepthWrite_StencilWrite:
		case DepthNop_StencilNop:
			return 0; // old DSAT_Writable

		case DepthRead_StencilNop:
		case DepthRead_StencilWrite:
			return 1; // old DSAT_ReadOnlyDepth

		case DepthNop_StencilRead:
		case DepthWrite_StencilRead:
			return 2; // old DSAT_ReadOnlyStencil

		case DepthRead_StencilRead:
			return 3; // old DSAT_ReadOnlyDepthAndStencil
		}
		// should never happen
		check(0);
		return -1;
	}
	static const uint32 MaxIndex = 4;

private:
	inline Type ExtractDepth() const
	{
		return (Type)(Value & DepthMask);
	}
	inline Type ExtractStencil() const
	{
		return (Type)(Value & StencilMask);
	}
};

class FRHIDepthRenderTargetView
{
public:
	FTextureRHIParamRef			Texture;

	ERenderTargetLoadAction		DepthLoadAction;
	ERenderTargetStoreAction	DepthStoreAction;
	ERenderTargetLoadAction		StencilLoadAction;

private:
	ERenderTargetStoreAction	StencilStoreAction;
	FExclusiveDepthStencil		DepthStencilAccess;

public:
	ERenderTargetStoreAction	GetStencilStoreAction() const { return StencilStoreAction; }
	FExclusiveDepthStencil		GetDepthStencilAccess() const { return DepthStencilAccess; }

	explicit FRHIDepthRenderTargetView() :
		Texture(nullptr),
		DepthLoadAction(ERenderTargetLoadAction::ENoAction),
		DepthStoreAction(ERenderTargetStoreAction::ENoAction),
		StencilLoadAction(ERenderTargetLoadAction::ENoAction),
		StencilStoreAction(ERenderTargetStoreAction::ENoAction),
		DepthStencilAccess(FExclusiveDepthStencil::DepthNop_StencilNop)
	{
		Validate();
	}

	// common case
	explicit FRHIDepthRenderTargetView(FTextureRHIParamRef InTexture, ERenderTargetLoadAction InLoadAction, ERenderTargetStoreAction InStoreAction) :
		Texture(InTexture),
		DepthLoadAction(InLoadAction),
		DepthStoreAction(InStoreAction),
		StencilLoadAction(InLoadAction),
		StencilStoreAction(InStoreAction),
		DepthStencilAccess(FExclusiveDepthStencil::DepthWrite_StencilWrite)
	{
		Validate();
	}

	explicit FRHIDepthRenderTargetView(FTextureRHIParamRef InTexture, ERenderTargetLoadAction InLoadAction, ERenderTargetStoreAction InStoreAction, FExclusiveDepthStencil InDepthStencilAccess) :
		Texture(InTexture),
		DepthLoadAction(InLoadAction),
		DepthStoreAction(InStoreAction),
		StencilLoadAction(InLoadAction),
		StencilStoreAction(InStoreAction),
		DepthStencilAccess(InDepthStencilAccess)
	{
		Validate();
	}

	explicit FRHIDepthRenderTargetView(FTextureRHIParamRef InTexture, ERenderTargetLoadAction InDepthLoadAction, ERenderTargetStoreAction InDepthStoreAction, ERenderTargetLoadAction InStencilLoadAction, ERenderTargetStoreAction InStencilStoreAction) :
		Texture(InTexture),
		DepthLoadAction(InDepthLoadAction),
		DepthStoreAction(InDepthStoreAction),
		StencilLoadAction(InStencilLoadAction),
		StencilStoreAction(InStencilStoreAction),
		DepthStencilAccess(FExclusiveDepthStencil::DepthWrite_StencilWrite)
	{
		Validate();
	}

	explicit FRHIDepthRenderTargetView(FTextureRHIParamRef InTexture, ERenderTargetLoadAction InDepthLoadAction, ERenderTargetStoreAction InDepthStoreAction, ERenderTargetLoadAction InStencilLoadAction, ERenderTargetStoreAction InStencilStoreAction, FExclusiveDepthStencil InDepthStencilAccess) :
		Texture(InTexture),
		DepthLoadAction(InDepthLoadAction),
		DepthStoreAction(InDepthStoreAction),
		StencilLoadAction(InStencilLoadAction),
		StencilStoreAction(InStencilStoreAction),
		DepthStencilAccess(InDepthStencilAccess)
	{
		Validate();
	}

	void Validate() const
	{
		//ensureMsgf(DepthStencilAccess.IsDepthWrite() || DepthStoreAction == ERenderTargetStoreAction::ENoAction, TEXT("Depth is read-only, but we are performing a store.  This is a waste on mobile.  If depth can't change, we don't need to store it out again"));
		//ensureMsgf(DepthStencilAccess.IsStencilWrite() || StencilStoreAction == ERenderTargetStoreAction::ENoAction, TEXT("Stencil is read-only, but we are performing a store.  This is a waste on mobile.  If stencil can't change, we don't need to store it out again"));
	}

	bool operator==(const FRHIDepthRenderTargetView& Other) const
	{
		return
			Texture == Other.Texture &&
			DepthLoadAction == Other.DepthLoadAction &&
			DepthStoreAction == Other.DepthStoreAction &&
			StencilLoadAction == Other.StencilLoadAction &&
			StencilStoreAction == Other.StencilStoreAction &&
			DepthStencilAccess == Other.DepthStencilAccess;
	}
};

class FRHISetRenderTargetsInfo
{
public:
	// color render targets info.
	FRHIRenderTargetView	ColorRenderTarget[MaxSimultaneousRenderTargets];
	int32					NumColorRenderTargets;
	bool					bClearColor;

	// depth/stencil render target info.
	FRHIDepthRenderTargetView	DepthStencilRenderTarget;
	bool						bClearDepth;
	bool						bClearStencil;

	FRHISetRenderTargetsInfo() :
		NumColorRenderTargets(0),
		bClearColor(false),
		bClearDepth(false),
		bClearStencil(false)
	{}

	FRHISetRenderTargetsInfo(int32 InNumColorRenderTargets, const FRHIRenderTargetView* InColorRenderTargets, const FRHIDepthRenderTargetView& InDepthStencilRenderTarget) :
		NumColorRenderTargets(InNumColorRenderTargets),
		bClearColor(InNumColorRenderTargets > 0 && InColorRenderTargets[0].LoadAction == ERenderTargetLoadAction::EClear),
		DepthStencilRenderTarget(InDepthStencilRenderTarget),
		bClearDepth(InDepthStencilRenderTarget.Texture && InDepthStencilRenderTarget.DepthLoadAction == ERenderTargetLoadAction::EClear),
		bClearStencil(InDepthStencilRenderTarget.Texture && InDepthStencilRenderTarget.StencilLoadAction == ERenderTargetLoadAction::EClear)
	{
		check(InNumColorRenderTargets > 0 && InColorRenderTargets);
		for (int32 Index = 0; Index < InNumColorRenderTargets; ++Index)
		{
			ColorRenderTarget[Index] = InColorRenderTargets[Index];
		}
	}

	void SetClearDepthStencil(bool bInClearDepth, bool bInClearStencil = false)
	{
		if (bInClearDepth)
		{
			DepthStencilRenderTarget.DepthLoadAction = ERenderTargetLoadAction::EClear;
		}
		if (bInClearStencil)
		{
			DepthStencilRenderTarget.StencilLoadAction = ERenderTargetLoadAction::EClear;
		}
		bClearDepth = bInClearDepth;
		bClearStencil = bInClearStencil;
	}
};

class FRHICustomPresent : public FRHIResource
{
	explicit FRHICustomPresent(FRHIViewport* InViewport)
		: ViewportRHI(InViewport)
	{
	}

	virtual ~FRHICustomPresent() {}

	// Called when viewport is resized.
	virtual void OnBackBufferResize() = 0;

	// Called from render thread to see if a native present will be requested for this frame.
	virtual bool NeedsNativePresent() = 0;

	// Called from RHI thread to perform custom present.
	virtual bool Present(int32& InOutSyncInterval) = 0;

	// Called from RHI thread after native Present has been called
	virtual void PostPresent() {};

	// Called when rendering thread is acquired
	virtual void OnAcquireThreadOwnership() {}
	// Called when rendering thread is released
	virtual void OnReleaseThreadOwnership() {}

protected:
	// Weak reference, don't create a circular dependency that would prevent the viewport from being destroyed.
	FRHIViewport* ViewportRHI;
};

typedef FRHICustomPresent*					FCustomPresentRHIParamRef;
typedef std::shared_ptr<FRHICustomPresent>	FCustomPresentRHIRef;

// Template magic to convert an FRHI*Shader to its enum
template<typename TRHIShader> struct TRHIShaderToEnum {};
template<> struct TRHIShaderToEnum<FRHIVertexShader> { enum { ShaderFrequency = SF_Vertex }; };
template<> struct TRHIShaderToEnum<FRHIHullShader> { enum { ShaderFrequency = SF_Hull }; };
template<> struct TRHIShaderToEnum<FRHIDomainShader> { enum { ShaderFrequency = SF_Domain }; };
template<> struct TRHIShaderToEnum<FRHIPixelShader> { enum { ShaderFrequency = SF_Pixel }; };
template<> struct TRHIShaderToEnum<FRHIGeometryShader> { enum { ShaderFrequency = SF_Geometry }; };
template<> struct TRHIShaderToEnum<FVertexShaderRHIParamRef> { enum { ShaderFrequency = SF_Vertex }; };
template<> struct TRHIShaderToEnum<FHullShaderRHIParamRef> { enum { ShaderFrequency = SF_Hull }; };
template<> struct TRHIShaderToEnum<FDomainShaderRHIParamRef> { enum { ShaderFrequency = SF_Domain }; };
template<> struct TRHIShaderToEnum<FPixelShaderRHIParamRef> { enum { ShaderFrequency = SF_Pixel }; };
template<> struct TRHIShaderToEnum<FGeometryShaderRHIParamRef> { enum { ShaderFrequency = SF_Geometry }; };
template<> struct TRHIShaderToEnum<FVertexShaderRHIRef> { enum { ShaderFrequency = SF_Vertex }; };
template<> struct TRHIShaderToEnum<FHullShaderRHIRef> { enum { ShaderFrequency = SF_Hull }; };
template<> struct TRHIShaderToEnum<FDomainShaderRHIRef> { enum { ShaderFrequency = SF_Domain }; };
template<> struct TRHIShaderToEnum<FPixelShaderRHIRef> { enum { ShaderFrequency = SF_Pixel }; };
template<> struct TRHIShaderToEnum<FGeometryShaderRHIRef> { enum { ShaderFrequency = SF_Geometry }; };


struct FBoundShaderStateInput
{
	FVertexDeclarationRHIParamRef VertexDeclarationRHI;
	FVertexShaderRHIParamRef VertexShaderRHI;
	FHullShaderRHIParamRef HullShaderRHI;
	FDomainShaderRHIParamRef DomainShaderRHI;
	FPixelShaderRHIParamRef PixelShaderRHI;
	FGeometryShaderRHIParamRef GeometryShaderRHI;

	FORCEINLINE FBoundShaderStateInput()
		: VertexDeclarationRHI(nullptr)
		, VertexShaderRHI(nullptr)
		, HullShaderRHI(nullptr)
		, DomainShaderRHI(nullptr)
		, PixelShaderRHI(nullptr)
		, GeometryShaderRHI(nullptr)
	{
	}

	FORCEINLINE FBoundShaderStateInput(
		FVertexDeclarationRHIParamRef InVertexDeclarationRHI,
		FVertexShaderRHIParamRef InVertexShaderRHI,
		FHullShaderRHIParamRef InHullShaderRHI,
		FDomainShaderRHIParamRef InDomainShaderRHI,
		FPixelShaderRHIParamRef InPixelShaderRHI,
		FGeometryShaderRHIParamRef InGeometryShaderRHI
	)
		: VertexDeclarationRHI(InVertexDeclarationRHI)
		, VertexShaderRHI(InVertexShaderRHI)
		, HullShaderRHI(InHullShaderRHI)
		, DomainShaderRHI(InDomainShaderRHI)
		, PixelShaderRHI(InPixelShaderRHI)
		, GeometryShaderRHI(InGeometryShaderRHI)
	{
	}
};
