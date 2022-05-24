#include "RoomTileMap8.h"

RoomTileMap8* RoomTileMap8::Inst_ = nullptr;

RoomTileMap8::RoomTileMap8() 
{
}

RoomTileMap8::~RoomTileMap8() 
{
}

void RoomTileMap8::Start()
{
	Inst_ = this;
	SetPosition({ -4841 - 612 , -179 });
	TileMap_.TileRangeSetting(11, 6, { 64, 64 });
	ColMap_ = GameEngineImageManager::GetInst()->Find("Room8ColMap.bmp");

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

