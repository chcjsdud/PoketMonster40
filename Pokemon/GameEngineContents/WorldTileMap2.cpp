#include "WorldTileMap2.h"

WorldTileMap2* WorldTileMap2::Inst_ = nullptr;

WorldTileMap2::WorldTileMap2()
{
}

WorldTileMap2::~WorldTileMap2() 
{
}

void WorldTileMap2::Start()
{
	Inst_ = this;
	SetPosition({ -4696, -5432 });
	TileMap_.TileRangeSetting(66, 30, { 64, 64 });
	ColMap_ = GameEngineImageManager::GetInst()->Find("ColMap2.bmp");

	//for (int y = 19; y < 23; y++)
	//{
	//	for (int x = 49; x < 54; x++)
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