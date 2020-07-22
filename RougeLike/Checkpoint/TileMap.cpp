#include "TileMap.h"



TileMap::TileMap(TileList ^ startTileList, int startNCols, int startNRows)//constructor
{
	tileList = startTileList;
	NRows = startNRows;
	NCols = startNCols;
	map = gcnew array<int, 2>(NRows, NCols);
	VisibleMap = gcnew array<bool, 2>(NRows, NCols);
}

bool TileMap::isTileWalkable(int row, int col ) { //takes in a tile's row and column number and assigns the 2d array value to a variable which is sent to the IsTileWalkable method 
	int mapValue = map[row,col];
	return tileList->IsTileWalkable(mapValue);
}

void TileMap::SetTileMap(array<int, 2>^ newMap)//sets up a new map
{
	map = newMap;
}

void TileMap::SetMapEntry(int col, int row, int tileIndex) //takes a row and column and assigns them to a single index value
{
	map[row,col ] = tileIndex;
	
}

int TileMap::GetMapEntry(int col, int row) //returns the 2d array value given a row and column
{
	return map[row, col];
}

Bitmap ^ TileMap::GetMapCellBitmap(int row, int col) //returns a bitmap value given a column and row value
{
	int mapValue = map[row, col];
	return tileList->GetTileBitmap(mapValue);
}


void TileMap::ResetFog()//resets every tile back to fog
{
	for (int r = 0; r < NRows; r++)
	{
		for (int c = 0; c < NCols; c++)
		{
			VisibleMap[r, c] = false;
		}
	}
}





