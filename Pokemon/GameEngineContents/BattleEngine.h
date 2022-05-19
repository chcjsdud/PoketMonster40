#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Pokemon.h"
#include "PokemonInfoManager.h"
#include "ContentEnum.h"

// Ό³Έν :
class BattleEngine : public GameEngineActor
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

	void BattleTurn(PokemonInfo* _HitPokemon, PokemonInfo* _TargetPokemon, const PokemonSkill* _Skill);

protected:
	void Update() override;
	void Start() override;

private:

};

