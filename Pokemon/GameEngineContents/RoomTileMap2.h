#pragma once
#include "PokemonTileMap.h"

// 설명 : 레드집 1층
class RoomTileMap2 : public PokemonTileMap
{
private:
	static RoomTileMap2* Inst_;

public:
	static RoomTileMap2* GetInst()
	{
		return Inst_;
	}

public:
	// constrcuter destructer
	RoomTileMap2();
	~RoomTileMap2();

	// delete Function
	RoomTileMap2(const RoomTileMap2& _Other) = delete;
	RoomTileMap2(RoomTileMap2&& _Other) noexcept = delete;
	RoomTileMap2& operator=(const RoomTileMap2& _Other) = delete;
	RoomTileMap2& operator=(RoomTileMap2&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
};

