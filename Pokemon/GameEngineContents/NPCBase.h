#pragma once
#include <GameEngine/GameEngineActor.h>
#include "PokemonTileMap.h"

enum class NPCState
{
	Idle,
	Up,
	Down,
	Left,
	Right,
};
// Ό³Έν :
class NPCBase : public GameEngineActor
{
public:
	// constrcuter destructer
	NPCBase();
	~NPCBase();

	// delete Function
	NPCBase(const NPCBase& _Other) = delete;
	NPCBase(NPCBase&& _Other) noexcept = delete;
	NPCBase& operator=(const NPCBase& _Other) = delete;
	NPCBase& operator=(NPCBase&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override;

protected:
	void NPCMove();
	void NPCMoveAnim();
	PokemonTileMap* CurrentTileMap_;

	float NPCLerpX_;
	float NPCLerpY_;
	float NPCLerpTime_;
	float NPCNextMoveTime_;
	bool  IsMove_;

private:
	float4	StartPos_;
	float4	GoalPos_;
	float4	NPCMoveDir_;

	NPCState State_;
};

