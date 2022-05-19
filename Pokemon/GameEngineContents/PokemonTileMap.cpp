#include "PokemonTileMap.h"
#include <GameEngineBase/GameEngineDebug.h>

PokemonTileMap::PokemonTileMap() 
	: TileMap_(GameEngineRendererTileMap(this))
{
}

PokemonTileMap::~PokemonTileMap() 
{
}

float4 PokemonTileMap::GetWorldPostion(int _X, int _Y)
{
	//if (false == TileMap_.IsTile(_X, _Y))
	//{
	//	MsgBoxAssert("존재하지 않는 타일의 위치를 알려고 했습니다.");
	//}

	return GetPosition() + TileMap_.GetWorldPostion(_X, _Y);
}