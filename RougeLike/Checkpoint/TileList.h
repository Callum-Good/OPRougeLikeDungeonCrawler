//TileList holds the tiles on the map
#pragma once
#include "Tile.h"

ref class TileList
{
private:
	array<Tile^>^ tileArray;
	int nTiles;
public:
	TileList(int startNTiles);

	//Returns the bitmap of the tile at position
	//tileIndex in the TileList's array of Tile^
	Bitmap^ GetTileBitmap(int tileIndex);

	void SetTileArrayEntry(int tileIndex, String^ fileName, bool isWalkable);

	//Used to load up the array of Tile^
	//Places tileToEnter and location tileIndex of the array
	bool IsTileWalkable(int tileIndex);

};

