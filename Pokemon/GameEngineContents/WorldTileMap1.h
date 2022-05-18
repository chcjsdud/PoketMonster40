#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>

// Ό³Έν :
class WorldTileMap1 : public GameEngineActor
{
private: 
	static WorldTileMap1* Inst_;

public:
	static WorldTileMap1* GetInst()
	{
		return Inst_;
	}

	// constrcuter destructer
	WorldTileMap1();
	~WorldTileMap1();

	// delete Function
	WorldTileMap1(const WorldTileMap1& _Other) = delete;
	WorldTileMap1(WorldTileMap1&& _Other) noexcept = delete;
	WorldTileMap1& operator=(const WorldTileMap1& _Other) = delete;
	WorldTileMap1& operator=(WorldTileMap1&& _Other) noexcept = delete;

protected:

private:
	GameEngineRendererTileMap TileMap_;

	void Start() override;
};

