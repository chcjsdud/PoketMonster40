#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineSound.h>

#include "WorldMapLevel.h"

// Ό³Έν :
class BattleStartUI : public GameEngineActor
{
public:
	// constrcuter destructer
	BattleStartUI();
	~BattleStartUI();

	// delete Function
	BattleStartUI(const BattleStartUI& _Other) = delete;
	BattleStartUI(BattleStartUI&& _Other) noexcept = delete;
	BattleStartUI& operator=(const BattleStartUI& _Other) = delete;
	BattleStartUI& operator=(BattleStartUI&& _Other) noexcept = delete;

	void ChangeToBattleLevel(BattleNpcType _Type);

protected:
	void Start() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	GameEngineSoundPlayer BgmPlayer_;
	GameEngineRenderer* Renderer_;
	BattleNpcType Type_;
	float AnimTimer_;
	int Index_;

	void StartBattle();
};

