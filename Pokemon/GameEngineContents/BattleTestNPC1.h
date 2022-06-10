#pragma once
#include "BattleNPCInterface.h"
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class BattleTestNPC1 : public BattleNPCInterface, public GameEngineActor
{
public:
	// constrcuter destructer
	BattleTestNPC1();
	~BattleTestNPC1();

	// delete Function
	BattleTestNPC1(const BattleTestNPC1& _Other) = delete;
	BattleTestNPC1(BattleTestNPC1&& _Other) noexcept = delete;
	BattleTestNPC1& operator=(const BattleTestNPC1& _Other) = delete;
	BattleTestNPC1& operator=(BattleTestNPC1&& _Other) noexcept = delete;

protected:
	void Update() override;
	void Start() override;

private:

};

