#pragma once

#include "Object.h"

class UEngine : public UObject
{
public:
	UEngine() {}
	virtual ~UEngine() {}

public:
	float m_DisplayGamma	= 2.2f;
};

extern UEngine * GEngine;