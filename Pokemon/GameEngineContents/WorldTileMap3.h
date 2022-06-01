#pragma once
#include "PokemonTileMap.h"

// Ό³Έν :
class WorldTileMap3 : public PokemonTileMap
{
private:
	static WorldTileMap3* Inst_;

public:
	static WorldTileMap3* GetInst()
	{
		return Inst_;
	}

public:
	// constrcuter destructer
	WorldTileMap3();
	~WorldTileMap3();

	// delete Function
	WorldTileMap3(const WorldTileMap3& _Other) = delete;
	WorldTileMap3(WorldTileMap3&& _Other) noexcept = delete;
	WorldTileMap3& operator=(const WorldTileMap3& _Other) = delete;
	WorldTileMap3& operator=(WorldTileMap3&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void MakeFlowers();
};

