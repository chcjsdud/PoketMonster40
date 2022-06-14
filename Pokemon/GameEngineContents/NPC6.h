#pragma once
#include "NPCBase.h"

// Ό³Έν :
class InteractionText;
class NPC6 : public NPCBase
{
public:
	// constrcuter destructer
	NPC6();
	~NPC6();

	// delete Function
	NPC6(const NPC6& _Other) = delete;
	NPC6(NPC6&& _Other) noexcept = delete;
	NPC6& operator=(const NPC6& _Other) = delete;
	NPC6& operator=(NPC6&& _Other) noexcept = delete;

	void InteractionMove();
	void InteractionAnim();

	static bool InteractionMove_;
	static bool InteractionAnim_;
	static InteractionText* Text_;

protected:

private:
	void Start() override;
	void Update() override;

	GameEngineRenderer* PokemonCenterBall;
	GameEngineRenderer* PokemonCenterBallEffect;
	bool PokeBallEffect_;
	float InteractionTime_;
};

