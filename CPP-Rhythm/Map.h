#pragma once

#include "GlobalStd.h"
#include "Tile.h"

class Map
{
public:
	void Initialize(LPWSTR fileName);
private:
	Tile** tiles;
};
