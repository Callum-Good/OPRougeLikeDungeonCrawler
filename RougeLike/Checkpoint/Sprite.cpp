#include "Sprite.h"

Sprite::Sprite(Graphics ^ startCanvas, array<Bitmap^>^ startSpriteSheets,
	int startNFrames, Random ^ startRGen, int startWorldWidth, int startWorldHeight, int startSpeed, TileMap^ stileMap, int startHealth)
{
	canvas = startCanvas;
	spriteSheets = startSpriteSheets;
	rGen = startRGen;
	nFrames = startNFrames;
	currentFrame = 0;
	worldWidth = startWorldWidth;
	worldHeight = startWorldHeight;
	xPos = rGen->Next(worldWidth);
	yPos = rGen->Next(worldHeight);

	speed = startSpeed;
	xVel = speed;
	yVel = speed;

	tileMap = stileMap;

	frameWidth = (int)spriteSheets[0]->Width / nFrames;
	frameHeight = spriteSheets[0]->Height;

	spriteDirections = (ESpriteDirections)rGen->Next(4);
	velocityDirections = gcnew array<Point>(4);
	velocityDirections[0] = Point(1, 0); // East
	velocityDirections[1] = Point(0, 1); // South
	velocityDirections[2] = Point(-1, 0);// West
	velocityDirections[3] = Point(0, -1);// North

	IsDetected = false;

	//put health bar in playersprite child when create it
	MaxHealth = startHealth;
	Health = MaxHealth;
	healthBarHeight = 4;
	healthBarWidth = frameWidth;
}

void Sprite::SpawnInRoom(List<Room^>^ rooms)
{
	int randomRoom = rGen->Next(rooms->Count);

	Rectangle spawnRoom = rooms[randomRoom]->getWorldLocation();

	xPos = rGen->Next(spawnRoom.Left, spawnRoom.Right - frameWidth);
	yPos = rGen->Next(spawnRoom.Top, spawnRoom.Bottom - frameHeight);

}

void Sprite::ForcedDraw(int forcedX, int forcedY)//all sprites
{
	int startX = currentFrame * frameWidth;
	int startY = 0;
	Rectangle pixelsToDraw = Rectangle(startX, startY, frameWidth, frameHeight);
	Bitmap^ currentBitmap = spriteSheets[spriteDirections];
	canvas->DrawImage(currentBitmap, forcedX, forcedY, pixelsToDraw, GraphicsUnit::Pixel);
	drawHealthBar(forcedX, forcedY);

}

void Sprite::drawHealthBar(int xLocation, int yLocation)
{
	int healthBarDistanceHigh = 5;
	int calculateHealth = (int)healthBarWidth*Health / MaxHealth;

	Rectangle maxHealthRectangle = Rectangle(xLocation, yLocation - healthBarDistanceHigh, healthBarWidth, healthBarHeight);
	Rectangle healthRectangle = Rectangle(xLocation, yLocation - healthBarDistanceHigh, calculateHealth, healthBarHeight);

	canvas->FillRectangle(Brushes::Red, maxHealthRectangle);
	canvas->FillRectangle(Brushes::LightGreen, healthRectangle);
}

void Sprite::Move()//all sprites
{
	int xMove = xPos + (xVel * velocityDirections[spriteDirections].X);
	int yMove = yPos + (yVel * velocityDirections[spriteDirections].Y);

	if (checkTerrain(xMove, yMove)) {
		xPos = xMove;
		yPos = yMove;
	}
}

void Sprite::Collision() {//all sprites
	if (xPos < 0)
		xPos = 0;
	if (yPos < 0)
		yPos = 0;
	if (xPos + frameWidth > worldWidth)
		xPos = worldWidth - frameWidth;
	if (yPos + frameHeight > worldHeight)
		yPos = worldHeight - frameHeight;
}

bool Sprite::checkTerrain(int xMove, int yMove)
{
	int xPixel;		//
	int yPixel;

	switch (spriteDirections)
	{
	case ESpriteDirections::EAST:
		xPixel = xMove + (frameHeight / 2);
		yPixel = yMove + (frameHeight / 2);
		break;
	case ESpriteDirections::SOUTH:
		xPixel = xMove + (frameWidth / 2);
		yPixel = yMove + (frameHeight / 2);
		break;
	case ESpriteDirections::WEST:
		xPixel = xMove;
		yPixel = yMove + (frameHeight / 2);
		break;
	case ESpriteDirections::NORTH:
		xPixel = xMove + (frameHeight / 2);
		yPixel = yMove;
		break;
	default:
		break;
	}
	int col = xPixel / 48;
	int row = yPixel / 48;
	if (tileMap->isTileWalkable(row, col)) {
		return true;
	}
	else {
		return false;
	}
}

void Sprite::SetSpriteRecPos(int vXPos, int vYPos)//all sprites
{
	SpriteRect = Rectangle((vXPos + (frameWidth / 3)), (vYPos + (frameHeight / 3)), frameWidth / 3, frameHeight / 2);
}

void Sprite::UpdateFrame()//all sprites
{
	currentFrame = (currentFrame + 1) % nFrames;
}

void Sprite::CollidedWithMe(Sprite ^ otherSprite)
{
	//EnemySprite
}

void Sprite::chase(int pX, int pY)
{
	//enemySprite
}

double Sprite::ComputeAngleToTarget(Sprite ^ player)
{
	return 0.0;
}

void Sprite::changeDirectionState(double direct)
{
}

void Sprite::EnemyMove(int direct)
{
}

void Sprite::Spawn(List<Room^>^ rooms)
{
}


void Sprite::Wander(int pX, int pY)
{
	//enemySprite
}





