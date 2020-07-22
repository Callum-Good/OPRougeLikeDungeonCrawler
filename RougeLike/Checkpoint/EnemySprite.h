//Child of the Sprite class - hold functions for enemy sprites
#pragma once
#include "Sprite.h"
#include "SpriteList.h"

#define WANDER_PROB 3
#define MAX_DIRECTIONS 4

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;


ref class EnemySprite : Sprite
{
public:
	EnemySprite(Graphics^ startCanvas, array<Bitmap^>^ startSpriteSheets, int startNFrames, Random^ startRGen,
		int startWorldWidth, int startWorldHeight, int startSpeed, TileMap^ stileMap, int startHealth);
	virtual double ComputeAngleToTarget(Sprite ^ player) override;
	virtual void changeDirectionState(double direct) override;
	virtual void Wander(int pX, int pY) override;
	virtual void CollidedWithMe(Sprite^ otherSprite) override;
	virtual void EnemyMove(int direct) override;
	virtual void SetInViewport(bool inViewport) override { InViewport = inViewport; };
};

