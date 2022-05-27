#include "GameEngineRendererTileMap.h"

float4 GameEngineRendererTileMap::GetWorldPostion(int _X, int _Y)
{
	float4 ReturnPos = TileSize_;

	ReturnPos.x *= _X;
	ReturnPos.y *= _Y;
	ReturnPos += TileSizeHalf_;

	return ReturnPos;
}

TileIndex GameEngineRendererTileMap::GetTileIndex(const float4& _Pos)
{
	int ReturnX = static_cast<int>(_Pos.x / TileSize_.x);
	int ReturnY = static_cast<int>(_Pos.y / TileSize_.y);

	if (_Pos.x < 0)
	{
		ReturnX = -1;
	}

	if (_Pos.y < 0)
	{
		ReturnY = -1;
	}

	return { ReturnX, ReturnY };
}

void GameEngineRendererTileMap::DeleteTile(int _X, int _Y)
{

}