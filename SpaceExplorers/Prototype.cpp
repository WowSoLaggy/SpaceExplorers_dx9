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

	// Load xml objects file

	pugi::xml_document objsFile;
	pugi::xml_parse_result parseResult = objsFile.load_file(pPathToObjsFile.c_str());
	if (parseResult.status != 0)
	{
		echo("ERROR: Invalid object file. Error description: \"", parseResult.description(), "\".");
		return err_invalidObjsFile;
	}

	// Find "Things" node

	auto documentNode = objsFile.child("Document");
	if (documentNode == nullptr)
	{
		echo("ERROR: Can't parse objects file. Can't find the \"Document\" xml node.");
		return err_invalidObjsFile;
	}

	auto thingsNode = documentNode.child("Things");
	if (thingsNode == nullptr)
	{
		echo("ERROR: Can't parse objects file. Can't find the \"Things\" xml node.");
		return err_invalidObjsFile;
	}

	// Parse prototypes

	for (auto& it : thingsNode)
	{
		Prototype prototype;

		auto param = it.first_child();
		while (param != nullptr)
		{
			if (std::string("TypeName").compare(param.name()) == 0)
				prototype.TypeName() = param.text().as_string();
			else if (std::string("TextureFilePath").compare(param.name()) == 0)
				prototype.TextureFilePath() = param.text().as_string();
			else if (std::string("IsPassable").compare(param.name()) == 0)
				prototype.IsPassable() = param.text().as_bool();
			else if (std::string("IsVentilated").compare(param.name()) == 0)
				prototype.IsVentilated() = param.text().as_bool();
			else if (std::string("NeedsLattice").compare(param.name()) == 0)
				prototype.NeedsLattice() = param.text().as_bool();
			else if (std::string("NeedsFloor").compare(param.name()) == 0)
				prototype.NeedsFloor() = param.text().as_bool();
			else if (std::string("NeedsSpace").compare(param.name()) == 0)
				prototype.NeedsSpace() = param.text().as_bool();
			else
			{
				echo("ERROR: Invalid parameter in the objs file: \"", param.name(), "\".");
				return err_invalidObjsFile;
			}

			param = param.next_sibling();
		}

		s_prototypes.push_back(prototype);
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
		auto* pFloor = pTile->FindChild("Floor");
		if (pFloor == nullptr)
			return false;
		else if (pFloor->GetChilds().size() != 0)
			return false;
	}

	return true;
}
