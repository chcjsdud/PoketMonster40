#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentEnum.h"

class GameEngineRenderer;
class PokemonSkill : public GameEngineActor
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

	void Start() override;
	void Update() override;

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


	inline GameEngineRenderer* GetMyEffect()
	{
		return MyEffect_;
	}

	inline void SetMyEffect(GameEngineRenderer* _Image)
	{
		MyEffect_ = _Image;
	}

protected:

private:
	int Value_; //공격 스킬 혹은 방어나 버프 계산에 쓰일 값
	SkillType SkillType_; //스킬 종류 (공격, 방어 등
	PokemonType Type_; //스킬 자체 속성 (노말, 불 등

	GameEngineRenderer* MyEffect_;
};

