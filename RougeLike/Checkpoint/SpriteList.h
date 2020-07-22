#pragma once

#include "Sprite.h"
#include "PlayerSprite.h"
#include "EnemySprite.h"

#define AWARE 200


ref class SpriteList
{
private:
	Sprite ^ head;
	Sprite^ tail;

public:
	SpriteList(void);
	void AddSprite(Sprite^ newSprite);
	void ChaseSprite(Sprite^ player);
	void DeleteSprite(Sprite^ spriteToDelete);
	void DeleteAllDeadSprites();
	void UpdateSprite();
	void DrawSpritesInViewport(int vWorldX, int vWorldY);
	void CheckCollisions(Sprite^ otherSprite);
	void WorldCollisions();
	void Spawn(List<Room^>^ rooms);
	void CheckInViewport(int vWorldX, int vWorldY, int vPixelWidth, int vPixelHeight);
};
