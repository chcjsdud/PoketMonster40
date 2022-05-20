#include "RoomTileMap6.h"

RoomTileMap6* RoomTileMap6::Inst_ = nullptr;

RoomTileMap6::RoomTileMap6()
{
}

RoomTileMap6::~RoomTileMap6() 
{
}

void RoomTileMap6::Start()
{
	Inst_ = this;
	SetPosition({ -1769, -1568 + 32 });
	TileMap_.TileRangeSetting(11, 6, { 64, 64 });
	ColMap_ = GameEngineImageManager::GetInst()->Find("Room6ColMap.bmp");

	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 11; x++)
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
