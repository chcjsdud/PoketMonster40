#pragma once
#include "Item.h"

// ªÛ√≥æ‡	
class Potion : public Item
{
public:
	// constrcuter destructer
	Potion();
	~Potion();

	// delete Function
	Potion(const Potion& _Other) = delete;
	Potion(Potion&& _Other) noexcept = delete;
	Potion& operator=(const Potion& _Other) = delete;
	Potion& operator=(Potion&& _Other) noexcept = delete;
	
	void Recovery(class PokemonInfo* _MyPokemon);

protected:

private:

};

