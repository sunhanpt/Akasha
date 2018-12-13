#include "DynamicRHI.h"


struct FD3D11Adapter
{
	int32 AdapterIndex;
	//D3D11_FEATURE_LEVEL MaxSupportedFeatureLevel;
};

class FD3D11DynamicRHIModule : public IDynamicRHIModule
{
public:
	virtual void StartupModule() override;
	virtual FDynamicRHI* CreateRHI(ERHIFeatureLevel::Type RequestedFeatureLevel = ERHIFeatureLevel::Num) override;
private:

};