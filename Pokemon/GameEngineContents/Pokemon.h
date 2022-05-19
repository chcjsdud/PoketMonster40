#pragma once
#include "PokemonInfo.h"
#include <GameEngine/GameEngineActor.h>

class Pokemon : public GameEngineActor
{
public:
	Pokemon();
	~Pokemon();

	Pokemon(const Pokemon& _Other) = delete;
	Pokemon(Pokemon&& _Other) noexcept = delete;
	Pokemon& operator=(const Pokemon& _Other) = delete;
	Pokemon& operator=(Pokemon&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;

	inline PokemonInfo* GetInfo()
	{
		return MyInfo_;
	}

protected:

private:
	PokemonInfo* MyInfo_;
};

