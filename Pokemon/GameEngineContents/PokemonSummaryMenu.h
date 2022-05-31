#pragma once
#include <GameEngine/GameEngineActor.h>
#include "UIEnum.h"

class PokemonInfo;
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

	//상태 초기화
	void InitPokemonSummaryMenu(int _PokemonOrder);
private:
	PokemonInfo* PokemonInfo_;
	bool IsOn_; // Init함수가 실행되야 Update하게

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
	GameEngineRenderer* PokemonInfoRenderer_;
};

