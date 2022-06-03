#include "RoomTileMap7.h"

RoomTileMap7* RoomTileMap7::Inst_ = nullptr;

RoomTileMap7::RoomTileMap7() 
{
}

RoomTileMap7::~RoomTileMap7() 
{
}

void RoomTileMap7::Start()
{
	Inst_ = this;
	SetPosition({ -6841, -178});
	TileMap_.TileRangeSetting(10, 6, { 64, 64 });
	ColMap_ = GameEngineImageManager::GetInst()->Find("Room7ColMap.bmp");

	//for (int y = 0; y < 6; y++)
	//{
	//	for (int x = 0; x < 10; x++)
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

