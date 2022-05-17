#pragma once

// 설명 :
class PokemonSkill
{
public:
	// constrcuter destructer
	PokemonSkill();
	~PokemonSkill();

	// delete Function
	PokemonSkill(const PokemonSkill& _Other) = delete;
	PokemonSkill(PokemonSkill&& _Other) noexcept = delete;
	PokemonSkill& operator=(const PokemonSkill& _Other) = delete;
	PokemonSkill& operator=(PokemonSkill&& _Other) noexcept = delete;

protected:

private:
	int Value_; //공격 스킬 혹은 방어나 버프 계산에 쓰일 값

};

