#pragma once
#include "GlobalStd.h"
#include "Scene.h"
#include "Note.h"
#include "Type.h"
#include "Audio.h"
#include "Effect.h"

typedef enum
{
	FREE,
	Down,
	Stay,
	Up
} KeyState;

typedef struct
{
	int type;
	int line;
	int time;
	int endTime;
} NoteItem;

class GameScene : public Scene
{
public:
	GameScene(wstring mapName, wstring mp3File, string mapFile, int speed);
	
private:
	int offset = 450;
	int musicTime = 0;
	int noteIndex = 0;
	int score = 0;
	int combo = 0;
	int maxCombo = 0;
	int judgePos = 45;

	int life = 100;

	int startTime = clock();
	int totalTime = 0;

	string str = "";
	
	wstring mp3File;
	wstring mapName;
	string mapFile;

	Color lineColor[4];

	KeyState keys[4];

	int judgeStore[6] = { 0, };

	vector<NoteItem> notes;
	vector<Note> noteObjects;
	vector<Effect> effects;

	Audio musicAudio;

	void CheckLine(int line);
	int GetMusicTime();
	void ComboBreak();
	void AddLife(int life);
	void ShowEffect(int type, int line);
	Color ColorGradiant(int life);

public:
	bool IsEnded = false;
	
	void Initialize() override;
	void Run() override;
	void Update() override;
	void Render() override;

	int deltaTime = 0;
};

