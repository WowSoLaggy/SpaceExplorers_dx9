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


Thing* Thing::FindChild(const std::string& pChildName, int pDepth) const
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


Thing* Thing::HitTest()
{
	for (auto& child : m_childs)
	{
		if (RealThing* pRealThing = dynamic_cast<RealThing*>(child))
		{
			Thing* pThing = pRealThing->HitTest();
			if (pThing != nullptr)
				return pThing;
		}
	}

	return nullptr;
}
