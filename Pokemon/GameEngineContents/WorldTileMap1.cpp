#include "WorldTileMap1.h"

WorldTileMap1::WorldTileMap1() 
	: TileMap_(GameEngineRendererTileMap(this))
{
}

WorldTileMap1::~WorldTileMap1() 
{
}

void WorldTileMap1::Start()
{
	SetPosition({-1470 + 1000, -3885 - 1800});

	TileMap_.TileRangeSetting(70, 111, { 70, 70 });

	for (int y = 0; y < 111; y++)
	{
		for (int x = 0; x < 70; x++)
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
	TileMap_.CreateTile<Tile>(0, 0, "White.bmp", 10);
	TileMap_.CreateTile<Tile>(1, 1, "White.bmp", 10);
	TileMap_.CreateTile<Tile>(2, 2, "White.bmp", 10);

	//Tile* TmpTile = TileMap_.GetTile<Tile>(0, 0);
	//TmpTile->SetRenderer(CreateRenderer("White.bmp", 100, RenderPivot::CENTER, TileMap_.GetWorldPostion(0, 0)));
	//TmpTile->SetRenderer(CreateRenderer("White.bmp", 100, RenderPivot::CENTER, TileMap_.GetWorldPostion(1, 1)));
	//TmpTile->SetRenderer(CreateRenderer("White.bmp", 100, RenderPivot::CENTER, TileMap_.GetWorldPostion(2, 2)));
	//CreateRenderer("White.bmp", 100, RenderPivot::CENTER, { 0, 0 });
}

