#include "RoomTileMap1.h"

RoomTileMap1* RoomTileMap1::Inst_ = nullptr;

RoomTileMap1::RoomTileMap1() 
{
}

RoomTileMap1::~RoomTileMap1() 
{
}

void RoomTileMap1::Start()
{
	Inst_ = this;
	SetPosition({ -1769, -358 });
	TileMap_.TileRangeSetting(11, 7, { 64, 64 });
	ColMap_ = GameEngineImageManager::GetInst()->Find("Room1ColMap.bmp");

	//for (int y = 0; y < 7; y++)
	//{
	//	for (int x = 0; x < 11; x++)
	//	{
	//		if (x % 2 == 0 && y % 2 != 0)
	//		{
	//			TileMap_.CreateTile<Tile>(x, y, "White.bmp", 1);
	//		}
	//		else if (x % 2 != 0 && y % 2 == 0)
	//		{
	//			TileMap_.CreateTile<Tile>(x, y, "White.bmp", 1);
	//		}
	//	}
	//}
}
