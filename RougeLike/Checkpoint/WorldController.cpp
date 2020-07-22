#include "WorldController.h"



WorldController::WorldController(Graphics ^ startCanvas, Random ^ startRGen, Size ^ startCanvasSize)//constructor 
{
	mainCanvas = startCanvas;
	rGen = startRGen;
	nRows = 120;
	nCols = 180;

	tileList = gcnew TileList(NTILES);
	fillTileSet();
	tileMap = gcnew TileMap(tileList, nRows, nCols);
	tileSide = 48;
	viewPort = gcnew TileViewport(startCanvasSize, tileMap, mainCanvas);
	dunegon = gcnew Dungeon(rGen, nCols, nRows, viewPort->ViewportTilesWide, viewPort->ViewportTilesHigh);

	trolls = gcnew SpriteList();
	dragons = gcnew SpriteList();

	StartNewGame();
}

void WorldController::StartNewGame() //creates the player and assigns it to a variable, also sets up enemy sprites and a new level(random level generated each time)
{	
	player = createPlayer();
	createEnemys();
	setUpNewLevel();
}

void WorldController::RunGameCycle()
{
	
	viewPort->CentreViewPortAroundSprite(player);
	viewPort->ViewportDraw();
	playerUpdate();
	enemyUpdate();
}

void WorldController::KeyDown(KeyEventArgs ^ e)
{
	switch (e->KeyData)
	{
	case Keys::D:
		player->setDirection(EAST);
		break;
	case Keys::S:
		player->setDirection(SOUTH);
		break;
	case Keys::A:
		player->setDirection(WEST);
		break;
	case Keys::W:
		player->setDirection(NORTH);
		break;
	default:
		return;
	}
	player->Move();
}

void WorldController::KeyUp(KeyEventArgs ^ e)
{
	throw gcnew System::NotImplementedException();
}

void WorldController::fillTileSet()//assigns images to tiles and appropriate enums to tiles and sets if they're walkable or not
{
	tileList->SetTileArrayEntry(LAVA, "lava.png", false);
	tileList->SetTileArrayEntry(LAVA2, "lava.png", false);
	tileList->SetTileArrayEntry(WALL, "wall.png", false);
	tileList->SetTileArrayEntry(PATH, "path.png", true);
	tileList->SetTileArrayEntry(CORRIDOR, "corridor.bmp", true);
	tileList->SetTileArrayEntry(PADDING, "wall.png", false);
	tileList->SetTileArrayEntry(DOOR, "corridor.bmp", true);
}

void WorldController::setMapFromDungeon()//takes the generated dunegon and fills it with the correct tiles
{
	array<int, 2>^ map = dunegon->GenerateMap();
	tileMap->SetTileMap(map);
}

void WorldController::setUpNewLevel()//calls appropriate methods to set up the sprites and dunegon
{
	setMapFromDungeon();
	tileMap->ResetFog();
	player->Spawn(dunegon->Rooms);
	trolls->Spawn(dunegon->Rooms);
	dragons->Spawn(dunegon->Rooms);
}

//Runs the checks and methods for player during gameplay
void WorldController::playerUpdate()
{
	player->Collision();
	player->UpdateFrame();
	
	player->ForcedDraw(viewPort->ViewportPixelX / 2, viewPort->ViewportPixelY / 2);
	player->SetSpriteRecPos(viewPort->ViewportPixelX / 2, viewPort->ViewportPixelY / 2);
}

//Runs the checks and methods for enemys during gameplay
void WorldController::enemyUpdate()
{
	//trolls
	trolls->WorldCollisions();
	trolls->CheckInViewport(viewPort->ViewportWorldX, viewPort->ViewportWorldY ,viewPort->ViewportPixelX, viewPort->ViewportPixelY );
	trolls->UpdateSprite();
	trolls->DrawSpritesInViewport(viewPort->ViewportWorldX, viewPort->ViewportWorldY);
	trolls->CheckCollisions(player);
	trolls->DeleteAllDeadSprites();
	trolls->ChaseSprite(player);
	
	//dragons
	dragons->WorldCollisions();
	dragons->CheckInViewport(viewPort->ViewportWorldX, viewPort->ViewportWorldY,viewPort->ViewportPixelX, viewPort->ViewportPixelY );
	dragons->UpdateSprite();
	dragons->DrawSpritesInViewport(viewPort->ViewportWorldX, viewPort->ViewportWorldY);
	dragons->CheckCollisions(player);
	dragons->DeleteAllDeadSprites();
	dragons->ChaseSprite(player);
}

//creates each spritelist and fills with the sprites
void WorldController::createEnemys()
{
	for (int i = 0; i < NPCNUM; i++) {
		EnemySprite^ newSprite = createTrolls();
		trolls->AddSprite(newSprite);
	}
	for (int i = 0; i < NPCNUM; i++) {
		EnemySprite^ newSprite = createDragons();
		dragons->AddSprite(newSprite);
	}
}

//Sets up the players sprite sheet and directions
PlayerSprite ^ WorldController::createPlayer()
{
	int framesInChickenSpriteSheet = 8;
	int directions = 4;

	Bitmap^ east = gcnew Bitmap("Little Chicken Walk East 8.bmp"); //i created a file of backup images if we want to change these <------
	Bitmap^ south = gcnew Bitmap("Little Chicken Walk South 8.bmp");
	Bitmap^ west = gcnew Bitmap("Little Chicken Walk West 8.bmp");
	Bitmap^ north = gcnew Bitmap("Little Chicken Walk North 8.bmp");

	array<Bitmap^>^ chickenImages = gcnew array<Bitmap^>(directions);

	chickenImages[ESpriteDirections::EAST] = east;
	chickenImages[ESpriteDirections::SOUTH] = south;
	chickenImages[ESpriteDirections::WEST] = west;
	chickenImages[ESpriteDirections::NORTH] = north;

	for (int d = 0; d < directions; d++)
	{
		Color transparentColor = chickenImages[d]->GetPixel(0, 0);
		chickenImages[d]->MakeTransparent(transparentColor);
	}

	return gcnew PlayerSprite(mainCanvas, chickenImages, framesInChickenSpriteSheet, rGen, tileSide*COL, tileSide*ROW, 16, tileMap, PLAYERHEALTH);

}

//Sets up the trolls sprite sheet and directions
EnemySprite^ WorldController::createTrolls() {

	int framesSpriteSheet = 13;
	int directions = 4;

	Bitmap^ east = gcnew Bitmap("Grey Troll East.png");
	Bitmap^ south = gcnew Bitmap("Grey Troll South.png");
	Bitmap^ west = gcnew Bitmap("Grey Troll West.png");
	Bitmap^ north = gcnew Bitmap("Grey Troll North.png");

	array<Bitmap^>^ enemyImages = gcnew array<Bitmap^>(directions);

	enemyImages[ESpriteDirections::EAST] = east;
	enemyImages[ESpriteDirections::SOUTH] = south;
	enemyImages[ESpriteDirections::WEST] = west;
	enemyImages[ESpriteDirections::NORTH] = north;

	for (int d = 0; d < directions; d++)
	{
		Color transparentColor = enemyImages[d]->GetPixel(0, 0);
		enemyImages[d]->MakeTransparent(transparentColor);
	}

	return gcnew EnemySprite(mainCanvas, enemyImages, framesSpriteSheet, rGen, tileSide*COL, tileSide*ROW, MOVESPEED, tileMap, ENEMYHEALTH);//note: returns "EnemySprite"
}

//Sets up the dragon sprite sheet and directions
EnemySprite^ WorldController::createDragons() {
	int framesSpriteSheet = 9;
	int directions = 4;

	Bitmap^ east = gcnew Bitmap("Fire Dragon East.bmp");
	Bitmap^ south = gcnew Bitmap("Fire Dragon South.bmp");
	Bitmap^ west = gcnew Bitmap("Fire Dragon West.bmp");
	Bitmap^ north = gcnew Bitmap("Fire Dragon North.bmp");

	array<Bitmap^>^ enemyImages = gcnew array<Bitmap^>(directions);

	enemyImages[ESpriteDirections::EAST] = east;
	enemyImages[ESpriteDirections::SOUTH] = south;
	enemyImages[ESpriteDirections::WEST] = west;
	enemyImages[ESpriteDirections::NORTH] = north;

	for (int d = 0; d < directions; d++)
	{
		Color transparentColor = enemyImages[d]->GetPixel(0, 0);
		enemyImages[d]->MakeTransparent(transparentColor);
	}

	return gcnew EnemySprite(mainCanvas, enemyImages, framesSpriteSheet, rGen, tileSide*COL, tileSide*ROW, MOVESPEED, tileMap, ENEMYHEALTH);//note: returns "EnemySprite"
}
