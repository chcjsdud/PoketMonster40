#pragma once
#include "PokemonTileMap.h"

// 설명 : 상점
class RoomTileMap6 : public PokemonTileMap
{
private:
	static RoomTileMap6* Inst_;

public:
	static RoomTileMap6* GetInst()
	{
		return Inst_;
	}

public:
	// constrcuter destructer
	RoomTileMap6();
	~RoomTileMap6();

	// delete Function
	RoomTileMap6(const RoomTileMap6& _Other) = delete;
	RoomTileMap6(RoomTileMap6&& _Other) noexcept = delete;
	RoomTileMap6& operator=(const RoomTileMap6& _Other) = delete;
	RoomTileMap6& operator=(RoomTileMap6&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

