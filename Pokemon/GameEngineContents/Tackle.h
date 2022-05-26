#pragma once
#include "PokemonSkill.h"

// Ό³Έν :
class Tackle : public PokemonSkill
{
public:
	Tackle();
	~Tackle();

	Tackle(const Tackle& _Other) = delete;
	Tackle(Tackle&& _Other) noexcept = delete;
	Tackle& operator=(const Tackle& _Other) = delete;
	Tackle& operator=(Tackle&& _Other) noexcept = delete;

protected:

private:

};

