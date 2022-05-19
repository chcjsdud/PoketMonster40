#include "WorldTileMap1.h"

WorldTileMap1* WorldTileMap1::Inst_ = nullptr;

WorldTileMap1::WorldTileMap1()
{
}

WorldTileMap1::~WorldTileMap1()
{
}

void WorldTileMap1::Start()
{
	Inst_ = this;
	SetPosition({ -470, -5685 });
	TileMap_.TileRangeSetting(70, 111, { 64, 64 });
	ColMap_ = GameEngineImageManager::GetInst()->Find("ColMap.bmp");

	for (int i = 0; i < 8; i++)
	{
		TileMap_.CreateTile<Tile>(i, i, "White.bmp", 1);
	}

	//for (int y = 0; y < 111; y++)
	//{
	//	for (int x = 0; x < 70; x++)
	//	{
	//		if (x % 2 == 0 && y % 2 != 0)
	//		{
	//			TileMap_.CreateTile<Tile>(x, y, "White.bmp", 10);
	//		}
	//		else if (x % 2 != 0 && y % 2 == 0)
	//		{
	//			TileMap_.CreateTile<Tile>(x, y, "White.bmp", 10);
	//		}
	//	}
	//}
}

