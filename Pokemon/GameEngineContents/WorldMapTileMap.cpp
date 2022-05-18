#include "WorldMapTileMap.h"

WorldMapTileMap::WorldMapTileMap() 
	: Map1TileMap_(GameEngineRendererTileMap(this))
{
}

WorldMapTileMap::~WorldMapTileMap() 
{
}

void WorldMapTileMap::Start()
{
	//Map1TileMap_.TileRangeSetting(111, 70, {70, 70});
	//Tile* TmpTile = Map1TileMap_.GetTile<Tile>(0, 0);
	//TmpTile->SetRenderer(CreateRenderer("White.bmp", 100, RenderPivot::CENTER, Map1TileMap_.GetWorldPostion(0, 0)));
	//
 	//float4 Pos = Map1TileMap_.GetWorldPostion(0, 0);

	//Tile* TmpTile2 = Map1TileMap_->GetTile<Tile>(100, 60);
	//TmpTile2->SetRenderer(CreateRenderer("White.bmp"));
}

