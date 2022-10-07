#pragma once
#include <set>

#define g_pObjectManager ObjectManager::GetInstance()

class Object;

class ObjectManager
{
public:
	void AddObject( Object* const pObject )
	{
		objectSet.insert( pObject );
	}
	void RemoveObject( Object* const pObject )
	{
		objectSet.erase( pObject );
	}
	void Destroy()
	{
		objectSet.clear();
		assert( objectSet.empty() );
	}

private:
	SINGLETON( ObjectManager )

private:
	std::set<Object*> objectSet;
};

