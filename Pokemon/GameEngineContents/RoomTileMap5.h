#pragma once
#include "PokemonTileMap.h"

// 설명 : 치료소
class RoomTileMap5 : public PokemonTileMap
{
private:
	static RoomTileMap5* Inst_;

public:
	static RoomTileMap5* GetInst()
	{
		return Inst_;
	}

public:
	// constrcuter destructer
	RoomTileMap5();
	~RoomTileMap5();

	// delete Function
	RoomTileMap5(const RoomTileMap5& _Other) = delete;
	RoomTileMap5(RoomTileMap5&& _Other) noexcept = delete;
	RoomTileMap5& operator=(const RoomTileMap5& _Other) = delete;
	RoomTileMap5& operator=(RoomTileMap5&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

