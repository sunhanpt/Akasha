#pragma once

#include "Object.h"

class FSceneInterface;
class UWorld final: public UObject
{
public:

	FSceneInterface*				Scene;

public:
	UWorld() {}
	virtual ~UWorld() {}
};
