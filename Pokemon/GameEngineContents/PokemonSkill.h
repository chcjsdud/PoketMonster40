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

	inline int GetValue()
	{
		return Value_;
	}

	inline void SetValue(int _Value)
	{
		Value_ = _Value;
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
	PokemonType Type_;

	GameEngineRenderer* MyEffect_;
};

