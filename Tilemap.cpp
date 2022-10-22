#include "Tilemap.h"

#include <iostream>
#include <string>
#include <algorithm>
#include "game.h"
Tilemap::Tilemap() :
	tileSurface("assets/Spaceship-shooter#01/Wang tiles/02-Craters.png"),
	pos(Tmpl8::vec2(ScreenWidth / 2, ScreenHeight / 2)),
	lastPos(pos),
	col(new Collider(
		Tmpl8::vec2(
			0,
			0),
		Tmpl8::vec2(
			1,
			1),
		&pos))
{

	//add obstacles
	for (int y = 0; y < Y_TILES; y++)
		for (int x = 0; x < X_TILES; x++)
		{
			int index = x + y * X_TILES;
			if (tiles[index].IsBlocking) {

				Tmpl8::vec2 p = Tmpl8::vec2(x * tiles[index].xd + pos.x - static_cast<float>(OFFSET_X),
					y * tiles[index].yd + pos.y - static_cast<float>(OFFSET_Y));
				Tmpl8::vec2 offset = Tmpl8::vec2(tiles[index].pivotX, tiles[index].pivotY);
				p += offset;

				float xD = static_cast<float>(tiles[index].xd);
				float yD = static_cast<float>(tiles[index].yd);

				tiles[index].obs = new Obstacle(p, Collider(0, Tmpl8::vec2(xD - tiles[index].dimensionsX, yD - tiles[index].dimensionsY)));
				blockingTiles.push_back(tiles[index].obs);
				Tmpl8::Game::AddMoveable(tiles[index].obs);
			}
		}
}


Tilemap::~Tilemap()
{
	delete col;
}

void Tilemap::Render(Tmpl8::Surface* screen)
{
	//24x16 tiles
	for (int y = 0; y < Y_TILES; y++)
		for (int x = 0; x < X_TILES; x++)
		{

			int index = x + y * X_TILES;
			int tx = tiles[index].x;
			int ty = tiles[index].y;
			//uses some offset to center the tilemap
			DrawTile(screen, tx, ty,
				x * tiles[index].xd + static_cast<int>(pos.x) - OFFSET_X,
				y * tiles[index].yd + static_cast<int>(pos.y) - OFFSET_Y);
		}
	//debug
	for (int i = 0; i < blockingTiles.getCount(); i++) {
		Collider c = *blockingTiles[i]->getColl();
		screen->Box(c.min.x + c.pos->x, c.min.y + c.pos->y, c.max.x + c.pos->x, c.max.y + c.pos->y, 0xFF0000);
	}
	auto posText = std::string(std::to_string(pos.x) + " " + std::to_string(pos.y));
	screen->Print(posText.c_str(), 200, 10, 0xFF0000);
}


void Tilemap::Update(float deltaTime)
{
	for (int i = 0; i < blockingTiles.getCount(); i++) {

		blockingTiles[i]->Update(deltaTime);
	}
}



void Tilemap::DrawTile(Tmpl8::Surface* screen, int tx, int ty, int x, int y)
{
	int maxX = x + TILE_SIZE;
	int maxY = y + TILE_SIZE;

	//determine if the tile is offscreen

	if (maxX < 0 || x >= ScreenWidth || maxY < 0 || y >= ScreenHeight)
		return;
	//determine the clipping amount
	int minCX = std::max(0, x);
	int maxCX = std::min(ScreenWidth - 1, maxX);

	int minCY = std::max(0, y);
	int maxCY = std::min(ScreenHeight - 1, maxY);

	//difference of the clipped amount and the actual amount
	int addOffsetMinX = abs(minCX - x);

	int addOffsetMaxX = abs(maxCX - maxX);

	int addOffsetMinY = abs(minCY - y);

	int addOffsetMaxY = abs(maxCY - maxY);

	//add offset to the origin
	tx += addOffsetMinX;
	x += addOffsetMinX;
	ty += addOffsetMinY;
	y += addOffsetMinY;

	//substract the clipped amount from the tile
	int height = TILE_SIZE - addOffsetMaxY - addOffsetMinY;
	int width = TILE_SIZE - addOffsetMaxX - addOffsetMinX;


	//draw tile
	Tmpl8::Pixel* src = tileSurface.GetBuffer() + tx + ty * tileSurface.GetPitch();
	Tmpl8::Pixel* dst = screen->GetBuffer() + x + y * screen->GetPitch();

	for (int i = 0; i < height; i++)
	{
		memcpy(dst, src, sizeof(Tmpl8::Pixel) * width);
		src += tileSurface.GetPitch();
		dst += screen->GetPitch();
	}
}
