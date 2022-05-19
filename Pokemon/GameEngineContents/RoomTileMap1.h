#pragma once
#include "PokemonTileMap.h"

// 설명 : 지우집 2층
class RoomTileMap1 : public PokemonTileMap
{
private:
	static RoomTileMap1* Inst_;

public:
	static RoomTileMap1* GetInst()
	{
		return Inst_;
	}

public:
	// constrcuter destructer
	RoomTileMap1();
	~RoomTileMap1();

	// delete Function
	RoomTileMap1(const RoomTileMap1& _Other) = delete;
	RoomTileMap1(RoomTileMap1&& _Other) noexcept = delete;
	RoomTileMap1& operator=(const RoomTileMap1& _Other) = delete;
	RoomTileMap1& operator=(RoomTileMap1&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
};

