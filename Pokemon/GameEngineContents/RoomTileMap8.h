#pragma once
#include "PokemonTileMap.h"

// Ό³Έν :
class RoomTileMap8 : public PokemonTileMap
{
private:
	static RoomTileMap8* Inst_;

public:
	static RoomTileMap8* GetInst()
	{
		return Inst_;
	}

public:
	// constrcuter destructer
	RoomTileMap8();
	~RoomTileMap8();

	// delete Function
	RoomTileMap8(const RoomTileMap8& _Other) = delete;
	RoomTileMap8(RoomTileMap8&& _Other) noexcept = delete;
	RoomTileMap8& operator=(const RoomTileMap8& _Other) = delete;
	RoomTileMap8& operator=(RoomTileMap8&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
};

