#include "Tile.h"



Tile::Tile(String^ fileName, bool startIsWalkable)//constructor
{
	tileBitmap = gcnew Bitmap(fileName);
	IsWalkable = startIsWalkable;

}
