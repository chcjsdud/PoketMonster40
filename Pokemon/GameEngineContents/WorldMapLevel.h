#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class WorldTileMap1;
class RoomTileMap1;
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

protected:
	void Loading() override;
	void Update() override;

private:
	WorldTileMap1* WorldTileMap1Ptr;
	RoomTileMap1* RoomTileMap1Ptr;
};

