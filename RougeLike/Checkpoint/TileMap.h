//TilMap maps out the tiles in the dunegon. 
#pragma once
#include "Tile.h"
#include "TileList.h"


using namespace System::IO;

ref class TileMap
{
private:
	TileList^ tileList;
	array<int, 2>^ map;
public:
	TileMap(TileList^ startTileList, int startNCols, int startNRows);
	bool isTileWalkable(int row, int col);

	void SetTileMap(array<int, 2>^ newMap);

	//Place value tileIndex at location col, row of 2D map array
	void SetMapEntry(int col, int row, int tileIndex);

	int GetMapEntry(int col, int row); //Return the int value at location col, row of the map
	Bitmap^ GetMapCellBitmap(int row, int col);
	//void DrawMap(); //Draw the map to the canvas

	void ResetFog();

public:
	property int NCols;
	property int NRows;
	property array<bool, 2>^ VisibleMap;
};

