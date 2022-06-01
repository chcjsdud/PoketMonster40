#include "RoomTileMap3.h"

RoomTileMap3* RoomTileMap3::Inst_ = nullptr;

RoomTileMap3::RoomTileMap3()
{
}

RoomTileMap3::~RoomTileMap3()
{
}

void RoomTileMap3::Start()
{
	Inst_ = this;
	SetPosition({ -1769 - 65, 900 - 25 });
	TileMap_.TileRangeSetting(13, 7, { 64, 64 });
	ColMap_ = GameEngineImageManager::GetInst()->Find("Room3ColMap.bmp");

	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 13; x++)
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