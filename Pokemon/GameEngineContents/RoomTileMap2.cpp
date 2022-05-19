#include "RoomTileMap2.h"

RoomTileMap2* RoomTileMap2::Inst_ = nullptr;

RoomTileMap2::RoomTileMap2()
{
}

RoomTileMap2::~RoomTileMap2()
{
}

void RoomTileMap2::Start()
{
	Inst_ = this;
	SetPosition({ -3881, -366 });
	TileMap_.TileRangeSetting(12, 7, { 64, 64 });
	ColMap_ = GameEngineImageManager::GetInst()->Find("Room2ColMap.bmp");

	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 12; x++)
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
}