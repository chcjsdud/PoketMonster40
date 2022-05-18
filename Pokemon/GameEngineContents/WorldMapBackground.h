#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class WorldMapBackground : public GameEngineActor
{
public:
	// constrcuter destructer
	WorldMapBackground();
	~WorldMapBackground();

	// delete Function
	WorldMapBackground(const WorldMapBackground& _Other) = delete;
	WorldMapBackground(WorldMapBackground&& _Other) noexcept = delete;
	WorldMapBackground& operator=(const WorldMapBackground& _Other) = delete;
	WorldMapBackground& operator=(WorldMapBackground&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	GameEngineRenderer* WorldMap1_;
};

