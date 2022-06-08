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
	SetPosition({ -2500 - 736 , -6500 - 832 });
	TileMap_.TileRangeSetting(23, 26, { 64, 64 });
	ColMap_ = GameEngineImageManager::GetInst()->Find("GymColMap.bmp");

	//for (int y = 0; y < 26; y++)
	//{
	//	for (int x = 0; x < 23; x++)
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