#pragma once

class PokemonSkillInfo;
class PokemonSkill
{
public:
	PokemonSkill();
	~PokemonSkill();
	
	PokemonSkill(const PokemonSkill& _Other) = delete;
	PokemonSkill(PokemonSkill&& _Other) noexcept = delete;
	PokemonSkill& operator=(const PokemonSkill& _Other) = delete;
	PokemonSkill& operator=(PokemonSkill&& _Other) noexcept = delete;

	inline void SetInfo(PokemonSkillInfo* _Info)
	{
		MyInfo_ = _Info;
	}

	inline PokemonSkillInfo* GetInfo()
	{
		return MyInfo_;
	}

protected:

private:
	PokemonSkillInfo* MyInfo_;
};

