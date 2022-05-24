#pragma once
#include <GameEngineBase/GameEngineRandom.h>
#include "BattleLevel.h"
// Ό³Έν :
class BattleEngine
{
private:

	BattleEngine();
	~BattleEngine();

	// delete Function
	BattleEngine(const BattleEngine& _Other) = delete;
	BattleEngine(BattleEngine&& _Other) noexcept = delete;
	BattleEngine& operator=(const BattleEngine& _Other) = delete;
	BattleEngine& operator=(BattleEngine&& _Other) noexcept = delete;

public:
	static bool ComareSpeed(PokemonBattleState* _Player, PokemonBattleState* _Poe);
	static float AttackCalculation(const PokemonBattleState* _Att, PokemonBattleState* _Def, const PokemonSkill& _Skill);
	DamgeType ComparePokemonType(const PokemonType& _Attack, const PokemonType& _Defend);

};