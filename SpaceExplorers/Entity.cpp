#include "stdafx.h"
#include "Thing.h"

#include "Thing.h"


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
		if (Thing* pThing = dynamic_cast<Thing*>(child))
		{
			if (pThing->GetPrototype().TypeName().compare(pChildName) == 0)
				return pThing;

			auto* pGrandChild = pThing->FindChild(pChildName);
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
		if (Thing* pThing = dynamic_cast<Thing*>(child))
		{
			if (Entity* pHitThing = pThing->HitTest())
				return pHitThing;
		}
	}

	return nullptr;
}
