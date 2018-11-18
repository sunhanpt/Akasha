#pragma once

class UObject
{
public:
	UObject() {}
	virtual ~UObject() {}

public:
	virtual class UWorld* GetWorld() const;
};