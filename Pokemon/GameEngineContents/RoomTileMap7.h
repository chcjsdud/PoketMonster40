#pragma once
#include "PokemonTileMap.h"

// 설명 : 학교
class RoomTileMap7 : public PokemonTileMap
{
private:
	static RoomTileMap7* Inst_;

public:
	static RoomTileMap7* GetInst()
	{
		return Inst_;
	}

public:
	// constrcuter destructer
	RoomTileMap7();
	~RoomTileMap7();

	// delete Function
	RoomTileMap7(const RoomTileMap7& _Other) = delete;
	RoomTileMap7(RoomTileMap7&& _Other) noexcept = delete;
	RoomTileMap7& operator=(const RoomTileMap7& _Other) = delete;
	RoomTileMap7& operator=(RoomTileMap7&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};