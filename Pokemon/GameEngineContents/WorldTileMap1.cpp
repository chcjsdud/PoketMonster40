#include "WorldTileMap1.h"

WorldTileMap1::WorldTileMap1() 
	: TileMap_(GameEngineRendererTileMap(this))
{
}

WorldTileMap1::~WorldTileMap1() 
{
}

void WorldTileMap1::Start()
{
	//Inst_ = this;
	SetPosition({-471, -6157});
	TileMap_.TileRangeSetting(70, 111, { 64, 64 });

	//SetPosition({-3000 + 1000 -25, -3885 - 1800 - 10 });
	//TileMap_.TileRangeSetting(111, 111, { 64, 64 });

	for (int y = 0; y < 111; y++)
	{
		for (int x = 0; x < 70; x++)
		{
			if (x % 2 == 0 && y % 2 != 0)
			{
				TileMap_.CreateTile<Tile>(x, y, "White.bmp", 10);
			}
			else if (x % 2 != 0 && y % 2 == 0)
			{
				TileMap_.CreateTile<Tile>(x, y, "White.bmp", 10);
			}
		}
	}
	TileMap_.CreateTile<Tile>(0, 0, "White.bmp", 10);
	TileMap_.CreateTile<Tile>(1, 1, "White.bmp", 10);
	TileMap_.CreateTile<Tile>(2, 2, "White.bmp", 10);
}

