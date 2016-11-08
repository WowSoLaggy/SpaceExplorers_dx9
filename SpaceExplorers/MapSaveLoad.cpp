#include "stdafx.h"
#include "Map.h"

#include "RealThing.h"


const std::string Map::c_mapFolder = "Data/Maps/";


ErrCode Map::SaveToFile(const Map& pMap, const std::string& pFileName)
{
	LOG("Map::SaveToFile()");
	
	std::ofstream outFile(c_mapFolder + pFileName, std::ios::binary);
	if (!outFile.good())
	{
		echo("ERROR: Can't open file to write.");
		return err_cantSaveMapToFile;
	}


	auto writeInt = [&](const int& pValue)
	{
		outFile.write((char*)&pValue, sizeof(pValue));
	};
	auto writeString = [&](const std::string& pString)
	{
		writeInt(pString.size());
		outFile.write(pString.c_str(), pString.size());
	};
	auto writeVector = [&](const D3DXVECTOR3& pVector)
	{
		outFile.write((char*)&pVector.x, sizeof(pVector.x));
		outFile.write((char*)&pVector.y, sizeof(pVector.y));
		outFile.write((char*)&pVector.z, sizeof(pVector.z));
	};

	std::function<void(const RealThing* pChild)> writeChild = [&](const RealThing* pChild)
	{
		writeString(pChild->GetPrototype().TypeName());
		writeVector(pChild->Position());

		// TODO: save animation

		writeInt(pChild->GetChilds().size());
		for (auto* pChild : pChild->GetChilds())
			writeChild(dynamic_cast<RealThing*>(pChild));
	};


	writeInt(pMap.m_width);
	writeInt(pMap.m_height);

	for (auto& tile : pMap.m_tiles)
	{
		writeInt(tile.GetChilds().size());
		for (auto* pChild : tile.GetChilds())
			writeChild(dynamic_cast<RealThing*>(pChild));
	}

	return err_noErr;
}


ErrCode Map::LoadFromFile(Map*& pMap, const std::string& pFileName)
{
	LOG("Map::LoadFromFile()");

	pMap = nullptr;

	std::ifstream inFile(c_mapFolder + pFileName, std::ios::binary);
	if (!inFile.good())
	{
		echo("ERROR: Can't open file to read.");
		return err_cantLoadMapFromFile;
	}


	auto readInt = [&](int& pValue)
	{
		inFile.read((char*)&pValue, sizeof(pValue));
	};
	auto readString = [&](std::string& pString)
	{
		int size;
		readInt(size);
		pString.resize(size);
		inFile.read(&*pString.begin(), pString.size());
	};
	auto readVector = [&](D3DXVECTOR3& pVector)
	{
		inFile.read((char*)&pVector.x, sizeof(pVector.x));
		inFile.read((char*)&pVector.y, sizeof(pVector.y));
		inFile.read((char*)&pVector.z, sizeof(pVector.z));
	};

	std::function<RealThing*()> loadChild = [&]() -> RealThing*
	{
		std::string prototypeName;
		readString(prototypeName);

		D3DXVECTOR3 position;
		readVector(position);

		RealThing* pRealThing = new RealThing(prototypeName, position);

		int numChilds;
		readInt(numChilds);

		for (int i = 0; i < numChilds; ++i)
			pRealThing->AddChild(loadChild());

		return pRealThing;
	};


	int width, height;
	readInt(width);
	readInt(height);
	pMap = new Map(width, height);

	for (auto& tile : pMap->m_tiles)
	{
		int numChilds;
		readInt(numChilds);

		for (int i = 0; i < numChilds; ++i)
			tile.AddChild(loadChild());
	}

	return err_noErr;
}
