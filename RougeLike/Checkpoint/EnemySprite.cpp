#include "EnemySprite.h"



EnemySprite::EnemySprite(Graphics ^ startCanvas, array<Bitmap^>^ startSpriteSheets, int startNFrames, Random ^ startRGen,//constructor
	int startWorldWidth, int startWorldHeight, int startSpeed, TileMap ^ stileMap, int startHealth)
	: Sprite(startCanvas, startSpriteSheets, startNFrames, startRGen,
		startWorldWidth, startWorldHeight, startSpeed, stileMap, startHealth)
{
	//
	InViewport = false;
}

//Computes the angle to the target player and converts it to degrees from radians
double EnemySprite::ComputeAngleToTarget(Sprite^ player)
{
	double angle;

	int xDelta = player->SpriteRect.X - SpriteRect.X;
	int yDelta = player->SpriteRect.Y - SpriteRect.Y;

	if ((xDelta != 0) && (yDelta != 0))
	{
		angle = Math::Atan2(yDelta, xDelta);
	}
	else
		angle = 0.0;

	//converts to degrees
	angle = angle * (180.0f / Math::PI);

	//makes it not negative
	if (angle < 0)
	{
		angle = 360 - (-angle);
	}
	return angle;

}

//changes the sprites direction depending on what angle the player is away from it
void EnemySprite::changeDirectionState(double direct)
{
	//depending on angle to player change to that direction
	if (direct >= 225 && direct < 315) {
		setDirection(NORTH);
	}
	if (direct >= 315 || direct < 45)
	{
		setDirection(EAST);
	}
	if (direct >= 45 && direct < 135) {
		setDirection(SOUTH);
	}
	if (direct >= 135 && direct < 225) {
		setDirection(WEST);

	}
}

void EnemySprite::Wander(int pX, int pY)//takes the players position  
{
	int prob = rGen->Next(MAX_DIRECTIONS);

	switch (prob) {
	case 0:
		chase(pX, pY);
		break;
	case 1:
		chase(pX, pY);
		break;
	case 2:
		chase(pX, pY);
		break;
	case 3:
		chase(pX, pY);
		break;
	default:
		break;
	}
}

void EnemySprite::CollidedWithMe(Sprite ^ otherSprite) //takes in another sprite and checks the hit box of the sprite and checks if it overlaps with its own
{
	if (SpriteRect.IntersectsWith(otherSprite->SpriteRect)) {
		IsDetected = true;
	}
	else {
		IsDetected = false;
	}
}

void EnemySprite::EnemyMove(int direct)//
{
	int xMove = xPos + xVel;
	int yMove = yPos + yVel;
	if (checkTerrain(xMove, yMove)) {
		xPos = xMove;
		yPos = yMove;
	}
}




