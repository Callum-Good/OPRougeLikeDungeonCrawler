#include "TileViewport.h"


TileViewport::TileViewport(Size^ startCanvasSize, TileMap^ startMap, Graphics^ startCanvas)//constructor
{

	backgroundMap = startMap;
	canvas = startCanvas;
	tileSide = 48;
	ViewportTilesHigh = startCanvasSize->Height / tileSide + 1;
	ViewportTilesWide = startCanvasSize->Width / tileSide + 1;

	ViewportPixelX = ViewportTilesWide * tileSide;
	ViewportPixelY = ViewportTilesHigh * tileSide;

	//ViewportWorldX = 1000;
	//ViewportWorldY = 1000;
}


void TileViewport::ViewportDraw()//computes where to draw the viewport based ViewPortWorldX & Y 
{
	int viewPortTileX = ViewportWorldX / tileSide;
	int viewPortTileY = ViewportWorldY / tileSide;

	int viewPortOffSetX = ViewportWorldX % tileSide;
	int viewPortOffSetY = ViewportWorldY % tileSide;

	for (int r = viewPortTileY; r < viewPortTileY + 12; r++)
	{
		for (int c = viewPortTileX; c < viewPortTileX + 18; c++)
		{
			int fogRow = (r + (ViewportTilesHigh / 2)) - 5;
			int fogCol = (c + (ViewportTilesWide / 2)) - 8;

			backgroundMap->VisibleMap[fogRow, fogCol] = true;
		}
	}

	for (int r = viewPortTileY; r <= (viewPortTileY + ViewportTilesHigh); r++)
	{
		for (int c = viewPortTileX; c <= (viewPortTileX + ViewportTilesWide); c++)
		{
			int screenY = ((r - viewPortTileY) * tileSide) - viewPortOffSetY;
			int screenX = ((c - viewPortTileX) * tileSide) - viewPortOffSetX;

			Bitmap^ tileImage = backgroundMap->GetMapCellBitmap(r, c);

			Rectangle rec = Rectangle(screenX, screenY, tileSide, tileSide);//sets where the visible tiles (i.e. not the gray fog tiles) will be

			if (backgroundMap->VisibleMap[r, c])
			{
				canvas->DrawImage(tileImage, rec);
			}
			else
			{
				canvas->FillRectangle(Brushes::SlateGray, rec);
			}

		}
	}
}

void TileViewport::MoveRelativeToPlayer(int spriteX, int spriteY)	//computes where to move the viewport by taking in two integers from the player moving and uses that to compute where the viewport tiles will be
{
	ViewportPixelX = spriteX - ((viewportTilesWide * tileSide) / 2);
	ViewportPixelY = spriteY - ((viewportTilesHigh * tileSide) / 2);
	BoundsChecking();
	ViewportTileX = ViewportPixelX / tileSide;
	ViewportTileY = ViewportPixelY / tileSide;
}


void TileViewport::BoundsChecking()//checks if the viewport is about to go off of the screen and adjusts it's location to stay on the window
{
	if (ViewportPixelX < 0) ViewportPixelX = 0;
	if (ViewportPixelX > (99 - viewportTilesWide) * tileSide) ViewportPixelX = (99 - viewportTilesWide) * tileSide;
	if (ViewportPixelY < 0) ViewportPixelY = 0;
	if (ViewportPixelY > (49 - viewportTilesHigh) * tileSide) ViewportPixelY = (49 - viewportTilesHigh) * tileSide;
}

void TileViewport::CentreViewPortAroundSprite(PlayerSprite^ player)//computes the players position and centers the viewport around it
{
	ViewportWorldX = player->xPos - (ViewportPixelX / 2);
	ViewportWorldY = player->yPos - (ViewportPixelY / 2);
}