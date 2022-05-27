#pragma once
#include <GameEngine/GameEngineActor.h>
#include "UIEnum.h"


class PokemonSummaryMenu : public GameEngineActor
{
	enum class PokemonSummaryMenuType
	{
		PokemonInfo,
		PokemonAbility,
		PokemonSkill,
		Max
	};
public:
	PokemonSummaryMenu();
	~PokemonSummaryMenu();


	PokemonSummaryMenu(const PokemonSummaryMenu& _Other) = delete;
	PokemonSummaryMenu(const PokemonSummaryMenu&& _Other) noexcept = delete;
	PokemonSummaryMenu& operator=(const PokemonSummaryMenu& _Ohter) = delete;
	PokemonSummaryMenu& operator=(const PokemonSummaryMenu&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
	//리소스 초기화
	void InitRenderer_();
	void InitFonts_();
	//fsm
	void ChangeState(PokemonSummaryMenuType _State);
	void UpdateState();

	void PokemonInfoStart();
	void PokemonInfoUpdate();

	PokemonSummaryMenuType CurState_;
	//렌더러
	GameEngineRenderer* TopMenuRenderer_;
	GameEngineRenderer* PokemonFrameRenderer_;
};

