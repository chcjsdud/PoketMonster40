#pragma once
#include <GameEngine/GameEngineLevel.h>

enum class BattleNpcType 
{
	None,
	Brock,
	Rival,
	Max,
};

// Ό³Έν :
class WorldMapLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	WorldMapLevel();
	~WorldMapLevel();

	// delete Function
	WorldMapLevel(const WorldMapLevel& _Other) = delete;
	WorldMapLevel(WorldMapLevel&& _Other) noexcept = delete;
	WorldMapLevel& operator=(const WorldMapLevel& _Other) = delete;
	WorldMapLevel& operator=(WorldMapLevel&& _Other) noexcept = delete;

	void StartBattleLevelByNPC(BattleNpcType _Type);
	void StartBattleLevelByWildeToWorld();

protected:
	void Loading() override;
	void Update() override;

	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;

private:
};

