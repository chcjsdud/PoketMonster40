#pragma once

// Ό³Έν :
class PokemonInfoManager
{
public:
	PokemonInfoManager();
	~PokemonInfoManager();

	PokemonInfoManager(const PokemonInfoManager& _Other) = delete;
	PokemonInfoManager(PokemonInfoManager&& _Other) noexcept = delete;
	PokemonInfoManager& operator=(const PokemonInfoManager& _Other) = delete;
	PokemonInfoManager& operator=(PokemonInfoManager&& _Other) noexcept = delete;

protected:

private:

};

