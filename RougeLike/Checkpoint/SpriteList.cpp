#include "SpriteList.h"

SpriteList::SpriteList()
{
	head = nullptr;
	tail = nullptr;
}

void SpriteList::AddSprite(Sprite ^ newSprite)
{
	if (tail == nullptr)
	{
		head = newSprite;
		tail = newSprite;
	}
	else
	{
		tail->Next = newSprite;
		tail = newSprite;
	}
}



void SpriteList::ChaseSprite(Sprite^ player)//checks if player is near sprite then chases and moves
{
	Sprite^ SpriteWalker = head;
	while (SpriteWalker != nullptr)
	{
		if (SpriteWalker->InViewport == true) {
			double direct = SpriteWalker->ComputeAngleToTarget(player);
			SpriteWalker->changeDirectionState(direct);
			SpriteWalker->Move();
		}
		SpriteWalker = SpriteWalker->Next;
	}
}

void SpriteList::DeleteSprite(Sprite ^ spriteToDelete)
{
	Sprite^ spriteWalker = head;
	if (spriteWalker == tail)
	{
		head = nullptr;
		tail = nullptr;
	}
	else if (spriteWalker == spriteToDelete) {
		head = spriteWalker->Next;
	}
	else
	{
		while (spriteWalker->Next != spriteToDelete) {
			spriteWalker = spriteWalker->Next;
		}

		spriteWalker->Next = spriteToDelete->Next;
		if (spriteToDelete == tail) {
			tail = spriteWalker;
		}
	}
}

void SpriteList::DeleteAllDeadSprites()
{
	Sprite^ SpriteWalker = head;
	while (SpriteWalker != nullptr)
	{
		if (SpriteWalker->IsDetected) {
			DeleteSprite(SpriteWalker);
		}
		SpriteWalker = SpriteWalker->Next;
	}
}



void SpriteList::UpdateSprite()
{
	Sprite^ SpriteWalker = head;
	while (SpriteWalker != nullptr)
	{
		SpriteWalker->UpdateFrame();
		SpriteWalker = SpriteWalker->Next;
	}
}

void SpriteList::DrawSpritesInViewport(int vWorldX, int vWorldY)
{
	Sprite^ SpriteWalker = head;
	while (SpriteWalker != nullptr)
	{
		int spriteViewportX = SpriteWalker->xPos - vWorldX;
		int spriteViewportY = SpriteWalker->yPos - vWorldY;
		if (SpriteWalker->InViewport == true) {
			SpriteWalker->ForcedDraw(spriteViewportX, spriteViewportY);
			SpriteWalker->SetSpriteRecPos(spriteViewportX, spriteViewportY);
		}

		SpriteWalker = SpriteWalker->Next;

	}
}

void SpriteList::CheckCollisions(Sprite ^ otherSprite)
{
	Sprite^ nodeWalker = head;
	int count = 0;
	while (nodeWalker != nullptr) {
		count++;
		if (nodeWalker->IsDetected == true) {
			nodeWalker->IsDetected = false;
		}
		else {
			nodeWalker->CollidedWithMe(otherSprite);
		}
		nodeWalker = nodeWalker->Next;
	}
}

void SpriteList::WorldCollisions()
{
	Sprite^ nodeWalker = head;
	int count = 0;
	while (nodeWalker != nullptr) {
		nodeWalker->Collision();
		nodeWalker = nodeWalker->Next;
	}
}

void SpriteList::Spawn(List<Room^>^ rooms)
{
	Sprite^ nodeWalker = head;
	int count = 0;
	while (nodeWalker != nullptr) {
		nodeWalker->SpawnInRoom(rooms);
		nodeWalker = nodeWalker->Next;
	}
}

//Checking if the sprite is in the viewport and sets boolean to true if they are
void SpriteList::CheckInViewport(int vWorldX, int vWorldY, int vPixelWidth, int vPixelHeight)
{
	Sprite^ SpriteWalker = head;
	while (SpriteWalker != nullptr)
	{
		SpriteWalker->SetInViewport(false);
		int spriteViewportX = SpriteWalker->xPos - vWorldX;
		int spriteViewportY = SpriteWalker->yPos - vWorldY;
		if (spriteViewportX >= 0 && spriteViewportY >= 0 && spriteViewportX <= vPixelWidth && spriteViewportY <= vPixelHeight) {
			SpriteWalker->SetInViewport(true);
		}

		SpriteWalker = SpriteWalker->Next;

	}
}


