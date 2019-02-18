#pragma once

#include "Object.h"

class UGameInstance : public UObject
{
public:
	UGameInstance() {}
	virtual ~UGameInstance() {}

public:
	virtual void Init();

	class UWorld* GetWorld() const;
	struct FWorldContext* GetWorldContext() const { return WorldContext; };
	class UEngine* GetEngine() const;
	class UGameViewportClient* GetGameViewportClient() const;

	virtual void StartGameInstance();
	/** virtual function to allow custom GameInstances an opportunity to do cleanup when shutting down */
	virtual void Shutdown();

protected:
	struct FWorldContext* WorldContext;
};
