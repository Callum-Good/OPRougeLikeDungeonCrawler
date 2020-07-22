#include "Dungeon.h"

Dungeon::Dungeon(Random^ randomGenerator, //constructor
	int startNRows, int startNCols,
	int halfViewportXOffset,
	int halfViewportYOffset)
{
	xOffset = halfViewportXOffset / 2;
	yOffset = halfViewportYOffset / 2;

	nRows = startNRows;
	nCols = startNCols;

	rGen = randomGenerator;
	map = gcnew array<int, 2>(nRows, nCols);
	Rooms = gcnew List<Room^>();
} 


array<int, 2>^ Dungeon::GenerateMap() //random number generator determines how many rooms to generate passes the result to the createRooms() method. the method returns a 2d array
{
	resetMap();
	int numRooms = rGen->Next(MINROOMS, MAXROOMS);         
	createRooms(numRooms);
	createCorridors();
	return map;
} 


void Dungeon::createRooms(int numberOfRooms)//creates a room and checks if it overlaps with any other room. if so another room is generated until it doesn't overlap with another room
{											//once created the room is added to the list "Rooms"
	Room^ newRoom = createNewRoom();       
	Rooms->Add(newRoom);       
	addRoomToMap(newRoom);       

	for (int i = 1; i < numberOfRooms; i++)
	{
		newRoom = createNewRoom();    
		bool hasOverlapped = checkOverlaps(newRoom);    

		while (hasOverlapped)           
		{
			newRoom = createNewRoom();
			hasOverlapped = checkOverlaps(newRoom);
		}

		Rooms->Add(newRoom);      
		addRoomToMap(newRoom);      
	}

} 


Room ^ Dungeon::createNewRoom()//determines the size of room - specifically, the number of rows and columns per room
{
	int roomNCols = rGen->Next(20, 25);
	int roomNRows = rGen->Next(20, 25);
	int roomStartCol = rGen->Next(xOffset, nCols - (2 * xOffset) - roomNCols);           
	int roomStartRow = rGen->Next(yOffset, nRows - (2 * yOffset) - roomNRows);              
	return gcnew Room(roomStartCol, roomStartRow, roomNCols, roomNRows);
} 


void Dungeon::addRoomToMap(Room ^ newRoom)//this method determines what type of tile to put at what index of the map. it uses the index values of where the rooms have been mapped to be. 
{
	int startRow = newRoom->MapRowLocation;
	int endRow = startRow + newRoom->NRows;
	int startCol = newRoom->MapColumnLocation;
	int endCol = startCol + newRoom->NCols;

	for (int r = startRow; r < endRow + 1; r++)
	{
		for (int c = startCol; c < endCol + 1; c++)
		{
			if (r == startRow || c == startCol || r == endRow || c == endCol)              
			{
				map[r, c] = PADDING;
			}
			else if (r == startRow + 1 || c == startCol + 1 || r == endRow - 1 || c == endCol - 1)      
			{
				map[r, c] = WALL;
			}
			else      
			{
				map[r, c] = PATH;
			}
		}
	}

}


bool Dungeon::checkOverlaps(Room ^ newRoom) //checks for overlaps by checking what tile lies at the index of the room that's to be created. 
{
	bool overlap = false;

	int startRow = newRoom->MapRowLocation;
	int endRow = startRow + newRoom->NRows;
	int startCol = newRoom->MapColumnLocation;
	int endCol = startCol + newRoom->NCols;


	for (int r = startRow; r < endRow + 1; r++)
	{
		for (int c = startCol; c < endCol + 1; c++)
		{
			if (map[r, c] == WALL)
			{
				overlap = true;
			}
			else if (map[r, c] == PADDING)
			{
				overlap = true;
			}
			else if (map[r, c] == PATH)
			{
				overlap = true;
			}
		}
	}

	return overlap;

} 


void Dungeon::createCorridors()//calls methods to create corridors
{
	for (int i = 0; i < Rooms->Count; i++)
	{
		if (i + 1 == Rooms->Count)             
		{
			addNewCorridor(Rooms[i], Rooms[0]);
		}
		else             
		{
			addNewCorridor(Rooms[i], Rooms[i + 1]);
		}
	}
}


void Dungeon::addNewCorridor(Room ^ roomA, Room ^ roomB)//computes the location of two rooms, and links them with a corridor
{
	Room^ lowerRoom;     
	Room^ higherRoom;    

	if (roomA->MapColumnLocation < roomB->MapColumnLocation)       
	{
		lowerRoom = roomA;
		higherRoom = roomB;
	}
	else       
	{
		lowerRoom = roomB;
		higherRoom = roomA;
	}

	int leftCenterCol = lowerRoom->MapColumnLocation + (lowerRoom->NCols / 2);
	int leftCenterRow = lowerRoom->MapRowLocation + (lowerRoom->NRows / 2);
	int rightCenterCol = higherRoom->MapColumnLocation + (higherRoom->NCols / 2);

	for (int i = leftCenterCol; i <= rightCenterCol; i++)
	{
		addCorridorToMap(leftCenterRow - 1, i - 1);           
		addCorridorToMap(leftCenterRow, i);
		addCorridorToMap(leftCenterRow + 1, i + 1);
	}


	if (roomA->MapRowLocation < roomB->MapRowLocation)       
	{
		lowerRoom = roomA;
		higherRoom = roomB;
	}
	else       
	{
		lowerRoom = roomB;
		higherRoom = roomA;
	}

	int bottomCenterRow = lowerRoom->MapRowLocation + (lowerRoom->NRows / 2);
	int topCenterCol = higherRoom->MapColumnLocation + (higherRoom->NCols / 2);
	int topCenterRow = higherRoom->MapRowLocation + (higherRoom->NRows / 2);

	for (int i = bottomCenterRow; i <= topCenterRow; i++)
	{
		addCorridorToMap(i - 1, rightCenterCol - 1);           
		addCorridorToMap(i, rightCenterCol);
		addCorridorToMap(i + 1, rightCenterCol + 1);
	}

} 


void Dungeon::addCorridorToMap(int row, int col)//checks where the corridors are - over lava or in a room
{
	if ((map[row, col] == LAVA) || (map[row, col] == LAVA2) || (map[row, col] == PADDING))
	{
		map[row, col] = CORRIDOR;
	}
	else if (map[row, col] == WALL)
	{
		map[row, col] = DOOR;
	}
} 


void Dungeon::resetMap()//resets the Room list and the maps index
{
	Rooms = gcnew List<Room^>();

	for (int r = 0; r < nRows; r++)
	{
		for (int c = 0; c < nCols; c++)
		{
			map[r, c] = rGen->Next(2);              
		}
	}
} 

