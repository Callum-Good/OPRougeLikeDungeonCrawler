#pragma once
#include "Cell.h"
#include "Dungeon.h"

#define MINROOMSIZE 5
#define MAXROOMSIZE 15
ref class Room
{
private:
	int width;
	int height;
	int xPos;
	int yPos;
	int xPosFar;
	int yPosFar;
	int center;
	int cols;
	int rows;
	Random^ rGen;
	array<Cell^, 2>^ map;
	Cell^ cell;
public:
	Room(Random^ startRGen, int startCols, int startRows);

	void MakeRoom();

	bool RoomOverlaps(Room^ otherRoom);
	void AddRoomToArray(array<Cell^, 2>^ roomPos);

	int getHeight() { return height; }
	int getWidth() { return width; }
	int getXPos() { return xPos; }
	int getYPos() { return yPos; }

	array<Cell^, 2>^ getRoomArray() { return map; }
};