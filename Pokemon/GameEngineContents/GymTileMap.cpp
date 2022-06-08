#include "GymTileMap.h"

GymTileMap* GymTileMap::Inst_ = nullptr;

GymTileMap::GymTileMap() 
{
}

GymTileMap::~GymTileMap() 
{
}

void GymTileMap::Start()
{
	Inst_ = this;
	SetPosition({ -2500 , -2500 });
	TileMap_.TileRangeSetting(11, 6, { 64, 64 });
	ColMap_ = GameEngineImageManager::GetInst()->Find("Room8ColMap.bmp");

	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 11; x++)
		{
			if (x % 2 == 0 && y % 2 != 0)
			{
				TileMap_.CreateTile<Tile>(x, y, "White.bmp", 1);
			}
			else if (x % 2 != 0 && y % 2 == 0)
			{
				TileMap_.CreateTile<Tile>(x, y, "White.bmp", 1);
			}
		}
	}
}