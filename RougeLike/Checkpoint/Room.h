//The room class contains information about the a room's location and size. 
#pragma once



using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;



ref class Room
{
private:
	int tileSide;

public:
	Room(int startColPos, int startRowPos, int startNCols, int startNRows);

	
	property int MapColumnLocation;
	property int MapRowLocation;
	property bool HasPortal;
	property int NCols;
	property int NRows;

	Rectangle getWorldLocation();
};

