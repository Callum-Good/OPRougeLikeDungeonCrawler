#include "Room.h"


Room::Room(int startColPos, int startRowPos, int startNCols, int startNRows)//constructor
{
	MapColumnLocation = startColPos;
	MapRowLocation = startRowPos;
	NCols = startNCols;
	NRows = startNRows;
	tileSide = 48;
	HasPortal = false;
}

Rectangle Room::getWorldLocation()//uses the location and size of a room and inputs it into the Rectangle funtion and returns a rectangle that is all the space on the mao that a room takes up
{
	int worldX = (MapColumnLocation + 2)*tileSide;
	int worldY = (MapRowLocation + 2)*tileSide;
	int worldWidth = (NCols - 3)*tileSide;
	int worldHeight = (NRows - 3)*tileSide;
	Rectangle worldLocation = Rectangle(worldX, worldY, worldWidth, worldHeight);
	return worldLocation;
}
