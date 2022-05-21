#include "BattleNPCInterface.h"
#include <GameEngineBase/GameEngineRandom.h>

BattleNPCInterface::BattleNPCInterface()
	: BattleNPC_(false)
	, CurrentPossessionPokemon_(nullptr)
{

}

BattleNPCInterface::~BattleNPCInterface() 
{

}

void BattleNPCInterface::GetRandomPokemon()
{
	//if (!CurrentPossessionPokemon_.empty())
	//{
	//	return;
	//}
	//GameEngineRandom Random();
	//
	// 랜덤 포켓몬 넣기
	//
}