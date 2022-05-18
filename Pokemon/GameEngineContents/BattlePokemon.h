#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class BattlePokemon : public GameEngineActor
{
public:
	// constrcuter destructer
	BattlePokemon();
	~BattlePokemon();

	// delete Function,
	BattlePokemon(const BattlePokemon& _Other) = delete;
	BattlePokemon(BattlePokemon&& _Other) noexcept = delete;
	BattlePokemon& operator=(const BattlePokemon& _Other) = delete;
	BattlePokemon& operator=(BattlePokemon&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:

	GameEngineRenderer* PlayerPokemon_;
	GameEngineRenderer* OpponentPokemon_;
	
};

