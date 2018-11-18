#pragma once
#include "Object.h"
#include <vector>
class ULevel;
class UActorComponent;
class AActor : public UObject
{
public:
	AActor() {}
	virtual ~AActor() {}

public:
	virtual void Tick(float detaSeconds);

protected:
	class USceneComponent* RootComponent;
	std::vector<AActor*> Children;
	std::vector<UActorComponent*> OwnedComponents;
};
