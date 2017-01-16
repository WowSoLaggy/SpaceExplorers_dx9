#include "stdafx.h"
#include "Entity.h"

#include "RealThing.h"


bool Entity::IsPassable() const
{
	for (auto& child : m_childs)
	{
		Entity* pThing = dynamic_cast<Entity*>(child);
		if (pThing && !pThing->IsPassable())
			return false;
	}

	return true;
}

bool Entity::IsVentilated() const
{
	for (auto& child : m_childs)
	{
		Entity* pThing = dynamic_cast<Entity*>(child);
		if (pThing && !pThing->IsVentilated())
			return false;
	}

	return true;
}


Entity* Entity::FindChild(const std::string& pChildName, int pDepth) const
{
	if (pDepth-- == 0)
		return nullptr;

	for (auto& child : m_childs)
	{
		if (RealThing* pRealThing = dynamic_cast<RealThing*>(child))
		{
			if (pRealThing->GetPrototype().TypeName().compare(pChildName) == 0)
				return pRealThing;

			auto* pGrandChild = pRealThing->FindChild(pChildName);
			if (pGrandChild != nullptr)
				return pGrandChild;
		}
	}

	return nullptr;
}


Entity* Entity::HitTest()
{
	for (auto& child : m_childs)
	{
		if (RealThing* pRealThing = dynamic_cast<RealThing*>(child))
		{
			Entity* pThing = pRealThing->HitTest();
			if (pThing != nullptr)
				return pThing;
		}
	}

	return nullptr;
}
