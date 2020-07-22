//The header for the dunegon class. This class controls how the rooms and corridors are generated, including where the rooms go and making sure they don't overlap.
//
#pragma once
#include "Tile.h"
#include "TileList.h"
#include "TileMap.h"
#include "Room.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;

#define MINROOMS 6
#define MAXROOMS 9
public enum TileType { LAVA, LAVA2, WALL, PATH, CORRIDOR, PADDING, DOOR };


ref class Dungeon
{
private:
	array<int, 2>^ map;
	Random^ rGen;
	int nRows;
	int nCols;
	int xOffset;
	int yOffset;

public:
	property List<Room^>^ Rooms;
public:
	Dungeon(Random ^ randomGenerator, int startNRows, int startNCols, int halfViewportXOffset, int halfViewportYOffset);

	array<int, 2>^ GenerateMap();
	void createRooms(int numberOfRooms);
	void addRoomToMap(Room^ newRoom);
	Room^ createNewRoom();
	void resetMap();
	bool checkOverlaps(Room^ newRoom);
	void createCorridors();
	void addNewCorridor(Room ^ roomA, Room ^ roomB);
	void addCorridorToMap(int row, int col);
};