#pragma once
#include "BattleNPCInterface.h"
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Pokemon;
class WildPokemonNPC : public BattleNPCInterface , public GameEngineActor
{
public:
	// constrcuter destructer
	WildPokemonNPC();
	~WildPokemonNPC();

	// delete Function
	WildPokemonNPC(const WildPokemonNPC& _Other) = delete;
	WildPokemonNPC(WildPokemonNPC&& _Other) noexcept = delete;
	WildPokemonNPC& operator=(const WildPokemonNPC& _Other) = delete;
	WildPokemonNPC& operator=(WildPokemonNPC&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
};

