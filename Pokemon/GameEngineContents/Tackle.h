#pragma once
#include "PokemonSkill.h"

// Ό³Έν :
class Tackle : public PokemonSkill
{
public:
	// constrcuter destructer
	Tackle();
	~Tackle();

	// delete Function
	Tackle(const Tackle& _Other) = delete;
	Tackle(Tackle&& _Other) noexcept = delete;
	Tackle& operator=(const Tackle& _Other) = delete;
	Tackle& operator=(Tackle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void End() override;

private:

};

