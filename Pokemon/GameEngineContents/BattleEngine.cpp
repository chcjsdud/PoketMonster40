#include "BattleEngine.h"
#include "BattleLevel.h"
#include "PokemonInfoManager.h"
#include <GameEngineBase/GameEngineDebug.h>

BattleEngine::BattleEngine() 
{
}

BattleEngine::~BattleEngine() 
{
}

void BattleEngine::Start()
{
	// Opponent
}

void BattleEngine::Update()
{

}

void BattlePage(Pokemon* _PlayerPokemon, Pokemon* _OpponentPokemon, const std::string& _PlayerSkill, const std::string& _OpponentSkill)
{
	// 스킬이 해당 포켓몬이 스킬 가지고 있는지 체크
	_PlayerPokemon->GetInfo()->GetSkill();
	PokemonSkill* PlayerSkill = PokemonInfoManager::GetInst().FindSkill("_PlayerSkill");
	if (PlayerSkill == nullptr)
	{
		MsgBoxAssert("스킬 명이 다릅니다")
	}
	PokemonSkill* OpponentSkill = PokemonInfoManager::GetInst().FindSkill("_OpponentSkill");
	if (PlayerSkill == nullptr)
	{
		MsgBoxAssert("스킬 명이 다릅니다")
	}



	//_PlayerPokemon->GetInfo()->
}