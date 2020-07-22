#include "TileList.h"



TileList::TileList(int startNTiles)//constructor
{
	tileArray = gcnew array<Tile^>(startNTiles);
}

Bitmap ^ TileList::GetTileBitmap(int tileIndex)//returns a bitmap value of a tile at a given index
{
	return tileArray[tileIndex]->tileBitmap;
}

void TileList::SetTileArrayEntry(int tileIndex, String^ fileName, bool isWalkable) //takes in tile information and stores it in an array
{
	Tile^ tileToEnter = gcnew Tile(fileName, isWalkable);
	tileArray[tileIndex] = tileToEnter;
}

bool TileList::IsTileWalkable(int tileIndex) { //takes in a tile and returns true or false depending on if it's walkable
	return tileArray[tileIndex]->IsWalkable;

}
