#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>

// Ό³Έν :
class PokemonTileMap : public GameEngineActor
{
public:
	// constrcuter destructer
	PokemonTileMap();
	~PokemonTileMap();

	// delete Function
	PokemonTileMap(const PokemonTileMap& _Other) = delete;
	PokemonTileMap(PokemonTileMap&& _Other) noexcept = delete;
	PokemonTileMap& operator=(const PokemonTileMap& _Other) = delete;
	PokemonTileMap& operator=(PokemonTileMap&& _Other) noexcept = delete;

	float4 GetWorldPostion(int _X, int _Y);
	inline GameEngineRendererTileMap& GetTileMap()
	{
		return TileMap_;
	}
	inline bool CanMove(int _X, int _Y)
	{
		float4 TestPos = TileMap_.GetWorldPostion(_X, _Y);
		int color = ColMap_->GetImagePixel(TestPos);
		if (RGB(0, 0, 0) != color)
		{
			return true;
		}
		
		return false;
	}

protected:
	GameEngineRendererTileMap TileMap_;
	GameEngineImage* ColMap_;

private:

};

