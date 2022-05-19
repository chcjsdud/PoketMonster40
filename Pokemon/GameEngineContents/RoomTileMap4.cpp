#include "RoomTileMap4.h"

RoomTileMap4* RoomTileMap4::Inst_ = nullptr;

RoomTileMap4::RoomTileMap4()
{
}

RoomTileMap4::~RoomTileMap4()
{
}

void RoomTileMap4::Start()
{
	Inst_ = this;
	SetPosition({ -3916, 780 });
	TileMap_.TileRangeSetting(13, 11, { 64, 64 });
	ColMap_ = GameEngineImageManager::GetInst()->Find("Room4ColMap.bmp");

	for (int y = 0; y < 11; y++)
	{
		for (int x = 0; x < 13; x++)
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