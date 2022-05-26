#pragma once
#include <GameEngineBase/GameEngineRandom.h>
#include "BattleLevel.h"
#include "PokemonSkillInfo.h"
// Ό³Έν :
enum class DamageType;
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
	static int AttackCalculation(const PokemonBattleState* _Att, const PokemonBattleState* _Def, PokemonSkillInfo* _Skill, const DamageType& _DamgeType);
	static DamageType ComparePokemonType(const PokemonBattleState* _Attack, const PokemonBattleState* _Defend);

};