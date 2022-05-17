#pragma once
#include <GameEngine/GameEngine.h>

class PokemonEngine : public GameEngine
{
public:
	// constrcuter destructer
	PokemonEngine();
	~PokemonEngine();

	// delete Function
	PokemonEngine(const PokemonEngine& _Other) = delete;
	PokemonEngine(PokemonEngine&& _Other) noexcept = delete;
	PokemonEngine& operator=(const PokemonEngine& _Other) = delete;
	PokemonEngine& operator=(PokemonEngine&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;

	void InitUI();
	void InitKey();

protected:

private:
	void ResourcesLoad();
	void ImageCut();
};

