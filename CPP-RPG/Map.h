#pragma once

#include "Global.h"
#include "Tile.h"

class Map
{
public:
	void Initialize(LPWSTR fileName);
private:
	Tile** tiles;
};
