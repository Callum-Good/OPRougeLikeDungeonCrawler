//Tile sets what image a tile is and if it's walkable 
#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class Tile
{
public:
	property Bitmap^ tileBitmap;
	property bool IsWalkable;
public:
	Tile(String^ fileName, bool startWalkable);
};

