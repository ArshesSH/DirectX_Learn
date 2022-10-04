#pragma once
class Object
{
public:
	Object();
	virtual ~Object();

	virtual void AddRef();
	virtual void Release();

protected:
	ULONG refCount;
};

