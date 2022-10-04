#include "framework.h"
#include "Object.h"

Object::Object()
	:
	refCount(1)
{
	g_pObjectManager->AddObject( this );
}

Object::~Object()
{
	g_pObjectManager->RemoveObject( this );
}

void Object::AddRef()
{
	++refCount;
}

void Object::Release()
{
	--refCount;
	if ( refCount == 0 )
	{
		delete this;
	}
}
