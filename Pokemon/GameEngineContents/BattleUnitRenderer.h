#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include "Pokemon.h"

// 설명 : BattleLevel에서 생성되는 인터페이스를 제외한 모든 렌더러를 가지고 있는 Actor
class BattleUnitRenderer : public GameEngineActor
{
public:
	// constrcuter destructer
	BattleUnitRenderer();
	~BattleUnitRenderer();

	// delete Function
	BattleUnitRenderer(const BattleUnitRenderer& _Other) = delete;
	BattleUnitRenderer(BattleUnitRenderer&& _Other) noexcept = delete;
	BattleUnitRenderer& operator=(const BattleUnitRenderer& _Other) = delete;
	BattleUnitRenderer& operator=(BattleUnitRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* PlayerPokemon_;
	GameEngineRenderer* OpponentPokemon_;


	GameEngineRenderer* PlayerRenderer_;
	GameEngineRenderer* OpponentRenderer_;


	float4 PlayerPokemonPos_;
	float4 OpponentPokemonPos_;
	float4 PlayerRendererPos_;
	float4 OpponentRenderer_Pos_;

	float PlayerTime_;
	float MoveSpeed;
};

