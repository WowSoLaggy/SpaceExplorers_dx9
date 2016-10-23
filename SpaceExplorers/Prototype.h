#pragma once

#ifndef INC_PROTOTYPE_H
#define INC_PROTOTYPE_H


#include "ErrCodes.h"
#include "Tile.h"


class Prototype : public Doh3d::GridItem
{
public:

	// GridItem

	Prototype() { }
	virtual ~Prototype() { }

	virtual int GetTi() const { return m_ti; }


	// Prototype

	std::string& TypeName() { return m_typeName; }
	const std::string& TypeName() const { return m_typeName; }

	std::string& TextureFilePath() { return m_textureName; }
	const std::string& TextureFilePath() const { return m_textureName; }

	int& Ti() { return m_ti; }
	const int& Ti() const { return m_ti; }


	bool& IsPassable() { return m_isPassable; }
	const bool& IsPassable() const { return m_isPassable; }

	bool& IsVentilated() { return m_isVentilated; }
	const bool& IsVentilated() const { return m_isVentilated; }


	bool& NeedsLattice() { return m_needsLattice; }
	const bool& NeedsLattice() const { return m_needsLattice; }

	bool& NeedsFloor() { return m_needsFloor; }
	const bool& NeedsFloor() const { return m_needsFloor; }

	bool& NeedsSpace() { return m_needsSpace; }
	const bool& NeedsSpace() const { return m_needsSpace; }


	bool CheckPrerequisites(Tile* pTile) const;


	static ErrCode Load();
	static ErrCode Unload();

	static ErrCode Init(const std::string& pPathToObjsFile);
	static Prototype& Find(const std::string& pTypeName);

	
private:

	std::string m_typeName;
	std::string m_textureName;
	int m_ti;

	bool m_isPassable;
	bool m_isVentilated;

	bool m_needsLattice;
	bool m_needsFloor;
	bool m_needsSpace;


	static std::vector<Prototype> s_prototypes;
};


#endif // INC_PROTOTYPE_H
