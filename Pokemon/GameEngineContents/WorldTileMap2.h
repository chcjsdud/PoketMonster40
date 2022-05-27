#pragma once
#include "PokemonTileMap.h"

// Ό³Έν :
class WorldTileMap2 : public PokemonTileMap
{
private:
	static WorldTileMap2* Inst_;

public:
	static WorldTileMap2* GetInst()
	{
		return Inst_;
	}

public:
	// constrcuter destructer
	WorldTileMap2();
	~WorldTileMap2();

	// delete Function
	WorldTileMap2(const WorldTileMap2& _Other) = delete;
	WorldTileMap2(WorldTileMap2&& _Other) noexcept = delete;
	WorldTileMap2& operator=(const WorldTileMap2& _Other) = delete;
	WorldTileMap2& operator=(WorldTileMap2&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void MakeFlowers();
};

