#pragma once
#include <GameEngine/GameEngineActor.h>
#include "UIEnum.h"

class PokemonInfo;
class GameEngineContentFont;
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
	void GetPlayerPokemon();
private:
	std::vector<PokemonInfo*> PokemonInfoList_;

	bool IsOn_; // Init함수가 실행되야 Update하게
	int CurrentOrder_;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	//리소스 초기화
	void InitRenderer_();
	void InitFonts_();

	//삭제
	void DestroyPokemonSummaryMenu();

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

	std::vector<GameEngineRenderer*> PokemonFrontRenderer_;

	//폰트
	std::vector<GameEngineContentFont*> LevelFonts_;
	std::vector< GameEngineContentFont*> NameFonts_;
	std::vector< GameEngineContentFont*> NumberFonts_;
	std::vector< GameEngineContentFont*> AllFonts_;


	//캐릭터 통통튀는거 구현
	float AccGravity_;
	float CurYPos_;
	bool IsJumpStart_;
	float JumpTime_;
	void PokemonJump();
	void PokemonJumpStart();
};

