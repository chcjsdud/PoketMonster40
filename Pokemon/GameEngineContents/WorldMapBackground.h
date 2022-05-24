#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

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
	GameEngineRenderer* WorldMap1_;
	GameEngineRenderer* RoomsRenderer_;

	void Start() override;
	void Update() override;
};

