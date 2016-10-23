#include "stdafx.h"
#include "Thing.h"


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
