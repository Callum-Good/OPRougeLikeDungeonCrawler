#include "Room.h"


Room::Room(Random^ startRGen, int startCols, int startRows)
{
	rGen = startRGen;
	cols = startCols;
	rows = startRows;
}

void Room::MakeRoom()
{
	//array <Room^>^ rooms = gcnew array<Room^>(roomNum);
	//for (int i = 0; i < roomNum; i++)
	//{
	//	rooms[i]->width = rGen->Next(MAXROOMSIZE,MINROOMSIZE);
	//	rooms[i]->height = rGen->Next(MAXROOMSIZE, MINROOMSIZE);
	//	rooms[i]->xPos = rGen->Next(maxWidth - width - 1);
	//	rooms[i]->yPos = rGen->Next(maxWidth - height - 1);

	//	bool failed = false;
	//	for (int x = 0; x < rooms->Length; x++) {
	//		if (rooms[i]->RoomOverlaps(rooms[x]) == true) {
	//			failed = true;
	//		}
	//	}

	//	if (failed = true) {
	//		i--;
	//	}
	//	else {
	//		
	//	}
	//}
	width = rGen->Next(MAXROOMSIZE, MINROOMSIZE);
	height = rGen->Next(MAXROOMSIZE, MINROOMSIZE);

	xPos = rGen->Next(cols - width);
	yPos = rGen->Next(rows - height);

	map = gcnew array<Cell^, 2>(width, height);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i == width - 1 || i == 0) {
				cell = gcnew Cell(WALL, true);
				map[i, j] = cell;
			}
			else if (j == height - 1 || j == 0) {
				cell = gcnew Cell(WALL, true);
				map[i, j] = cell;
			}
			else
			{
				cell = gcnew Cell(FLOOR, true);
				map[i, j] = cell;
			}
		}
	}

}

bool Room::RoomOverlaps(Room^ otherRoom) //return true if this room intersects with the provided room, "otherRoom"
{
	if (xPos <= otherRoom->xPosFar && xPosFar >= otherRoom->xPos && yPos <= otherRoom->yPosFar && otherRoom->yPosFar <= otherRoom->yPos) {
		return true;
	}
	else {
		return false;
	}
}

void Room::AddRoomToArray(array<Cell^, 2>^ roomPos)
{
	for (int col = xPos; col < (xPos + width); col++)
	{
		for (int row = yPos; row < (yPos + height); row++)
		{
			roomPos[col, row] = map[col - xPos, row - yPos];
		}
	}
}
