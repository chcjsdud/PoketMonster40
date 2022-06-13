#pragma once
#include "PokemonTileMap.h"

// 설명 : 오박사 연구소
class RoomTileMap4 : public PokemonTileMap
{
private:
	static RoomTileMap4* Inst_;

public:
	static RoomTileMap4* GetInst()
	{
		return Inst_;
	}

public:
	// constrcuter destructer
	RoomTileMap4();
	~RoomTileMap4();

	// delete Function
	RoomTileMap4(const RoomTileMap4& _Other) = delete;
	RoomTileMap4(RoomTileMap4&& _Other) noexcept = delete;
	RoomTileMap4& operator=(const RoomTileMap4& _Other) = delete;
	RoomTileMap4& operator=(RoomTileMap4&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	GameEngineRenderer* PokeballRender0_;	// 이상해씨
	GameEngineRenderer* PokeballRender1_;	// 꼬부기
	GameEngineRenderer* PokeballRender2_;	// 파이리
};

