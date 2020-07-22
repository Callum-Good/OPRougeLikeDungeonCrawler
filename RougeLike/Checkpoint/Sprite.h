#pragma once
#include "ESpriteDirections.h"
#include "TileMap.h"
#include "Room.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


ref class Sprite
{
private:
	Graphics ^ canvas;
	array<Bitmap^>^ spriteSheets;

	array<Point>^ velocityDirections;
	int nFrames;
	int currentFrame;
	TileMap^ tileMap;
	
	int worldWidth;
	int worldHeight;

	int healthBarHeight;
	int healthBarWidth;
protected:
	Random ^ rGen;
	ESpriteDirections spriteDirections;
	int speed;
	int xVel;
	int yVel;
	int MaxHealth;
	int Health;
	int frameWidth;
	int frameHeight;

public:
	Sprite ^ Next;
	property bool InViewport;
	property int xPos;
	property int yPos;
	Sprite(Graphics^ startCanvas, array<Bitmap^>^ startSpriteSheets, int startNFrames, Random^ startRGen,
		int startWorldWidth, int startWorldHeight, int startSpeed, TileMap^ stileMap, int startHealth);
	virtual void SpawnInRoom(List<Room^>^ rooms);
	//virtual void Spawn(List<Room^>^ rooms);
	void ForcedDraw(int forcedX, int forcedY);
	void drawHealthBar(int xLocation, int yLocation);
	void Move();
	void UpdateFrame();
	virtual void Wander(int pX, int pY);
	void Collision();
	bool checkTerrain(int xMove, int yMove);
	void setDirection(ESpriteDirections newDirection) { spriteDirections = newDirection; }
	virtual void CollidedWithMe(Sprite^ otherSprite);
	virtual void chase(int pX, int pY);
	virtual double ComputeAngleToTarget(Sprite ^ player);
	virtual void changeDirectionState(double direct);
	virtual void EnemyMove(int direct);
	virtual void SetInViewport(bool inViewPort) {};
	virtual void Spawn(List<Room^>^ rooms);





	//grayson's stuff
	void SetSpriteRecPos(int vXPos, int vYPos);

	property bool IsDetected;
	property Rectangle SpriteRect;
};

