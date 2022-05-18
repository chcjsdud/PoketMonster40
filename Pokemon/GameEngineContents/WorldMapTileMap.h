#pragma once
#include <GameEngine/GameEngineRendererTileMap.h>
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class WorldMapTileMap : public GameEngineActor
{
public:
	// constrcuter destructer
	WorldMapTileMap();
	~WorldMapTileMap();

	// delete Function
	WorldMapTileMap(const WorldMapTileMap& _Other) = delete;
	WorldMapTileMap(WorldMapTileMap&& _Other) noexcept = delete;
	WorldMapTileMap& operator=(const WorldMapTileMap& _Other) = delete;
	WorldMapTileMap& operator=(WorldMapTileMap&& _Other) noexcept = delete;

protected:

private:
	GameEngineRendererTileMap Map1TileMap_;

	void Start() override;
};

