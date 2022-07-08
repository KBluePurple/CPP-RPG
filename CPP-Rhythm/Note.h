#pragma once
#include "GameObject.h"
#include "GlobalStd.h"
#include "Type.h"

class Note : public GameObject
{
private:
	Vector2 prevPos = Vector2(0, 0);
	Vector2 newPos = Vector2(0, 0);
	string str = "";
	int offset = 0;
	
public:
	Note(int type, int line, int time, int offset);
	~Note();

public:
	void Update(float deltaTime) override;
	void Render() override;
	void Render(Color color);
	void Destroy() override;

public:
	int type;
	int line;
	int time;
	int lastDiffTime = 1000;
	bool IsDead = false;
};

