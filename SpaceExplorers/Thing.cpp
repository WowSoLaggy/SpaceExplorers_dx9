#include "stdafx.h"
#include "Thing.h"

#include "RealThing.h"


bool Thing::IsPassable() const
{
	for (auto& child : m_childs)
	{
		Thing* pThing = dynamic_cast<Thing*>(child);
		if (pThing && !pThing->IsPassable())
			return false;
	}

	return true;
}

bool Thing::IsVentilated() const
{
	for (auto& child : m_childs)
	{
		Thing* pThing = dynamic_cast<Thing*>(child);
		if (pThing && !pThing->IsVentilated())
			return false;
	}

	return true;
}


Thing* Thing::FindChild(const std::string& pChildName) const
{
	for (auto& child : m_childs)
	{
		RealThing* pRealThing = dynamic_cast<RealThing*>(child);
		if (pRealThing && pRealThing->GetPrototype().TypeName().compare(pChildName) == 0)
			return pRealThing;
	}

	return nullptr;
}
