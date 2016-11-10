#include "stdafx.h"
#include "Prototype.h"


std::vector<Prototype> Prototype::s_prototypes;


ErrCode Prototype::Load()
{
	LOG("Prototype::Load()");
	ErrCode3d err;

	for (auto& prototype : s_prototypes)
	{
		err = Doh3d::ResourceMan::GetTi(prototype.TextureFilePath(), prototype.Ti());
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't get TI for prototype (type name: \"", prototype.TypeName(), "\"): \"", prototype.TextureFilePath(), "\".");
			return err_cantGetTi;
		}

		D3DXVECTOR2 size = Doh3d::ResourceMan::GetTexture(prototype.Ti()).GetSize();
		prototype.m_size = D3DXVECTOR3(size.x, size.y, 0);
		prototype.m_size2 = D3DXVECTOR3(std::round(size.x / 2), std::round(size.y / 2), 0);
	}

	return err_noErr;
}

ErrCode Prototype::Unload()
{
	return err_noErr;
}


Prototype& Prototype::Find(const std::string& pTypeName)
{
	auto it = std::find_if(s_prototypes.begin(), s_prototypes.end(), [&](const Prototype& prototype) { return prototype.TypeName().compare(pTypeName) == 0; });
	return *it;
}


ErrCode Prototype::Init(const std::string& pPathToObjsFile)
{
	LOG("Prototype::Init()");
	ErrCode err;

	err = LoadPrototypesFromFile(pPathToObjsFile);
	if (err != err_noErr)
	{
		echo("ERROR: Can't load prototypes from the file.");
		return err;
	}

	return err_noErr;
}


bool Prototype::CheckPrerequisites(Tile* pTile) const
{
	if (pTile == nullptr)
		return false;

	if (NeedsSpace())
	{
		if (pTile->GetChilds().size() != 0)
			return false;
	}

	if (NeedsLattice())
	{
		auto* pLattice = pTile->FindChild("Lattice");
		if (pLattice == nullptr)
			return false;
		else if (pLattice->GetChilds().size() != 0)
			return false;
	}

	if (NeedsFloor())
	{
		auto* pFloor = pTile->FindChild("Floor", -1);
		if (pFloor == nullptr)
			return false;
		else if (pFloor->GetChilds().size() != 0)
			return false;
	}

	if (NeedsSurface())
	{
		auto* pTable = pTile->FindChild("Table", -1);
		if (pTable == nullptr)
		{
			auto* pFloor = pTile->FindChild("Floor", -1);
			if (pFloor == nullptr)
				return false;
			else if (pFloor->GetChilds().size() != 0)
				return false;
		}
		else if (pTable->GetChilds().size() != 0)
			return false;
	}

	return true;
}
