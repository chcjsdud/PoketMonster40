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


	static GameEngineRenderer* PlayerRenderer_;


protected:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* PlayerCurrentPokemon_;
	GameEngineRenderer* PoeCurrentPokemon_;


	GameEngineRenderer* OpponentRenderer_;


	float4 PlayerPokemonPos_;
	float4 OpponentPokemonPos_;
	float4 PlayerRendererPos_;
	float4 OpponentRenderer_Pos_;

	float PlayerTime_;
	float MoveSpeed;

	bool PlayerStop;//김예나 : 일정 위치 도착하면 멈추도록 할 조건문
	bool FirstMove;//김예나 : PlayerStop계속 들어오지 않도록 조건문용 bool
	float TimeCheck;

public:
	void DoomChit();
	bool GetPlayerStop()
	{
		return PlayerStop;
	}

	GameEngineRenderer* GetPlayerCurrentPokemon()
	{
		return PlayerCurrentPokemon_;
	}
};

