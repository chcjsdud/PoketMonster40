#include "RoomTileMap5.h"

RoomTileMap5* RoomTileMap5::Inst_ = nullptr;

RoomTileMap5::RoomTileMap5() 
{
}

RoomTileMap5::~RoomTileMap5() 
{
}

void RoomTileMap5::Start()
{
	Inst_ = this;
	SetPosition({ -3981, -1568});
	TileMap_.TileRangeSetting(15, 7, { 64, 64 });
	ColMap_ = GameEngineImageManager::GetInst()->Find("Room5ColMap.bmp");

	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 15; x++)
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
