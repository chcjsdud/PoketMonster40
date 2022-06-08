#pragma once
#include "PokemonTileMap.h"

// Ό³Έν :
class GymTileMap : public PokemonTileMap
{
private:
	static GymTileMap* Inst_;

public:
	static GymTileMap* GetInst()
	{
		return Inst_;
	}

public:
	// constrcuter destructer
	GymTileMap();
	~GymTileMap();

	// delete Function
	GymTileMap(const GymTileMap& _Other) = delete;
	GymTileMap(GymTileMap&& _Other) noexcept = delete;
	GymTileMap& operator=(const GymTileMap& _Other) = delete;
	GymTileMap& operator=(GymTileMap&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

