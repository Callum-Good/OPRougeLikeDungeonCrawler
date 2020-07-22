//The TileViewport is the visible space around the player that moves with the player sprite
#pragma once
#include "TileMap.h"
#include "PlayerSprite.h"


ref class TileViewport
{
private:
	TileList^ tileList;
	TileMap^ backgroundMap;
	int viewportTilesWide;
	int viewportTilesHigh;
	Graphics^ canvas;
	int col, row;
	int tileWidth;

	int tileSide;

public:
	property int ViewportPixelX;
	property int ViewportPixelY;

	property int ViewportTileX;
	property int ViewportTileY;

	property int ViewportTilesWide;
	property int ViewportTilesHigh;

	property int ViewportWorldX;
	property int ViewportWorldY;


	TileViewport(Size^ startCanvasSize, TileMap^ startBackgroundMap, Graphics^ startCanvas);
	void ViewportDraw();
	void MoveRelativeToPlayer(int spriteX, int spriteY);
	void BoundsChecking();

	void CentreViewPortAroundSprite(PlayerSprite^ player);

};

