#pragma once
#include "GlobalStd.h"

enum class TileType
{
	None,
	Block
};

class Tile
{
public:
	Vector2 Position;
	TileType Type;

	Tile() : Position(Vector2::Zero), Type(TileType::None) {}
	Tile(Vector2 position, TileType type) : Position(position), Type(type) {}
	
protected:
	virtual void Draw() = 0;
	virtual void Trigger() {};
};

