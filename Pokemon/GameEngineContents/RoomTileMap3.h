#pragma once
#include "PokemonTileMap.h"

// 설명 : 그린집 1층 
class RoomTileMap3 : public PokemonTileMap
{
private:
	static RoomTileMap3* Inst_;

public:
	static RoomTileMap3* GetInst()
	{
		return Inst_;
	}

public:
	// constrcuter destructer
	RoomTileMap3();
	~RoomTileMap3();

	// delete Function
	RoomTileMap3(const RoomTileMap3& _Other) = delete;
	RoomTileMap3(RoomTileMap3&& _Other) noexcept = delete;
	RoomTileMap3& operator=(const RoomTileMap3& _Other) = delete;
	RoomTileMap3& operator=(RoomTileMap3&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
};

