#pragma once
#include "Type.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	
public:
	FVector2 Position = FVector2(0, 0);

	void virtual Update(float dt) = 0;
	void virtual Render() = 0;
	void virtual Destroy() = 0;
};

