#include "stdafx.h"
#include "Prototype.h"


ErrCode Prototype::LoadPrototypesFromFile(const std::string& pPathToObjsFile)
{
	LOG("Prototype::ParsePrototypesFromFile()");
	ErrCode err;

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
			else if (std::string("TextureFileName").compare(param.name()) == 0)
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
			else if (std::string("NeedsSurface").compare(param.name()) == 0)
				prototype.NeedsSurface() = param.text().as_bool();
			else if (std::string("Behaviour").compare(param.name()) == 0)
				prototype.Behaviour() = ConvertStringToBehaviour(param.text().as_string());
			else if (std::string("Texture").compare(param.name()) == 0)
				; // Used only for editor
			else if (std::string("AnimationSet").compare(param.name()) == 0)
			{
				err = ParseAnimationSet(param, prototype);
				if (err != err_noErr)
				{
					echo("ERROR: Can't parse animation set.");
					return err;
				}
			}
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

ErrCode Prototype::ParseAnimationSet(const pugi::xml_node& pNode, Prototype& pPrototype)
{
	LOG("Prototype::ParseAnimationSet()");

	pPrototype.m_animationSet.Animations.clear();

	auto child = pNode.first_child();
	while (child != nullptr)
	{
		Doh3d::Animation animation;

		if (!child.child("Name") || !child.child("BeginFrame") || !child.child("EndFrame") || !child.child("Interval"))
		{
			echo("ERROR: Can't find all required nodes for animation.");
			return err_cantParseAnimation;
		}

		animation.Name = child.child("Name").text().as_string();
		animation.BeginFrame = child.child("BeginFrame").text().as_int();
		animation.EndFrame = child.child("EndFrame").text().as_int();
		animation.Interval = child.child("Interval").text().as_float();

		pPrototype.m_animationSet.Animations.push_back(animation);

		child = child.next_sibling();
	}

	return err_noErr;
}
