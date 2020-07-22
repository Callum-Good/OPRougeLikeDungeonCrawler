#include "PlayerSprite.h"



PlayerSprite::PlayerSprite(Graphics ^ startCanvas, array<Bitmap^>^ startSpriteSheets, int startNFrames, Random ^ startRGen,
	int startWorldWidth, int startWorldHeight, int startSpeed, TileMap ^ stileMap, int startHealth) :Sprite(startCanvas, startSpriteSheets, startNFrames, startRGen,
		startWorldWidth, startWorldHeight, startSpeed, stileMap, startHealth)
{
	//
}

void PlayerSprite::Spawn(List<Room^>^ rooms)
{
	int randomRoom;

	do
	{
		randomRoom = rGen->Next(rooms->Count);

	} while (rooms[randomRoom]->HasPortal);

	Rectangle spawnRoom = rooms[randomRoom]->getWorldLocation();
	xPos = rGen->Next(spawnRoom.Left, spawnRoom.Right - frameWidth);
	yPos = rGen->Next(spawnRoom.Top, spawnRoom.Bottom - frameHeight);
	
}
