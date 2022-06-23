#pragma once
#include "GlobalStd.h"
#include "Scene.h"

class Difficulty
{
public:
	string difficulty;
	string mapFile;
};

class Map
{
public:
	string title;
	wstring mp3File;
	vector<Difficulty> difficulties;
};

class MenuScene : public Scene
{
private:
	int speed;
	vector<Map> maps;
	bool keys[6];
	
	void DifficultySelect(Map map);
	void LoadScene(wstring mp3File, string mapFile);
	
public:
	virtual void Initialize() override;
	virtual void Run() override;
	virtual void Update() override;
	virtual void Render() override;
};

