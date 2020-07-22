#pragma once
#include "Sprite.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;


ref class PlayerSprite : Sprite
{
public:
	PlayerSprite(Graphics^ startCanvas, array<Bitmap^>^ startSpriteSheets, int startNFrames, Random^ startRGen,
		int startWorldWidth, int startWorldHeight, int startSpeed, TileMap^ stileMap, int startHealth);
	virtual void Spawn(List<Room^>^ rooms) override;
};

