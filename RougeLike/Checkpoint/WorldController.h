#pragma once

#include"TileMap.h"
#include"TileList.h"
#include"TileViewport.h"
#include"Dungeon.h"
//Controls how the game cycle
#include "PlayerSprite.h"
#include "EnemySprite.h"
#include "Sprite.h"

#define NTILES 48
#define COL 180
#define ROW 120
#define MOVESPEED 10
#define TILEWIDTH 48
#define NPCNUM 25
#define PLAYERHEALTH 10
#define ENEMYHEALTH 5


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class WorldController
{
private:
	Graphics^ mainCanvas;
	Random^ rGen;
	TileViewport^ viewPort;
	Dungeon^ dunegon;
	TileList^ tileList;
	TileMap^ tileMap;
	PlayerSprite^ player;
	SpriteList^ trolls;
	SpriteList^ dragons;

	int nRows;
	int nCols;
	int tileSide;
public:
	WorldController(Graphics ^ startCanvas, Random ^ startRGen, Size ^ startCanvasSize);

	void StartNewGame();
	void RunGameCycle();
	void KeyDown(KeyEventArgs^  e);
	void KeyUp(KeyEventArgs^  e);
private:
	void fillTileSet();
	void setMapFromDungeon();
	void setUpNewLevel();
	void playerUpdate();
	void enemyUpdate();
	void createEnemys();
	PlayerSprite^ createPlayer();
	EnemySprite ^ createTrolls();
	EnemySprite ^ createDragons();
};

