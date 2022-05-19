#pragma once
#include "ContentEnum.h"
#include <GameEngineBase/GameEngineNameObject.h>

class PokemonSkill : public GameEngineNameObject
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

	inline int GetValue()
	{
		return Value_;
	}

	inline void SetValue(int _Value)
	{
		Value_ = _Value;
	}

	inline PokemonType GetType()
	{
		return Type_;
	}

	inline void SetType(PokemonType _Type)
	{
		Type_ = _Type;
	}

	inline SkillType GetSkillType()
	{
		return SkillType_;
	}

	inline void SetSkillType(SkillType _SkillType)
	{
		SkillType_ = _SkillType;
	}

protected:

private:
	int Value_; //공격 스킬 혹은 방어나 버프 계산에 쓰일 값
	SkillType SkillType_; //스킬 종류 (공격, 방어 등
	PokemonType Type_; //스킬 자체 속성 (노말, 불 등
};

