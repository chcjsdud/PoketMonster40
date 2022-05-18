#pragma once
#include "Pokemon.h"
#include "PokemonInfoManager.h"
#include "ContentEnum.h"

// Ό³Έν :
class BattleEngine
{
public:
	// constrcuter destructer
	BattleEngine();
	~BattleEngine();

	// delete Function
	BattleEngine(const BattleEngine& _Other) = delete;
	BattleEngine(BattleEngine&& _Other) noexcept = delete;
	BattleEngine& operator=(const BattleEngine& _Other) = delete;
	BattleEngine& operator=(BattleEngine&& _Other) noexcept = delete;

	void BattlePokemon(Pokemon* _HitPokemon, Pokemon* _TargetPokemon, const PokemonSkill* _Skill);

protected:

private:

};

