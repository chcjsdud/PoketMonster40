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
		PokemonSkillSelect,
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
	int SkillSelect_CurrentOrder_;

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

	void PokemonAbilityStart();
	void PokemonAbilityUpdate();

	void PokemonSkillStart();
	void PokemonSkillUpdate();

	void PokemonSkillSelectStart();
	void PokemonSkillSelectUpdate();


	PokemonSummaryMenuType CurState_;


	//렌더러
	GameEngineRenderer* TopMenuRenderer_;
	GameEngineRenderer* PokemonFrameRenderer_;
	GameEngineRenderer* PokemonInfoRenderer_; //이거 탑메뉴 아래 큰창
	GameEngineRenderer* PokemonSkillGreenBoxRenderer_;
	GameEngineRenderer* PokemonSkillSelect_PokemonFrameRenderer_; //스킬 셀렉트에서 포켓몬 프레임
	GameEngineRenderer* PokemonSkillSelect_LeftGreenBox; //아이콘 아래에 뜨는 창


	std::vector<GameEngineRenderer*> PokemonFrontRenderer_;
	std::vector< GameEngineRenderer*> PokemonTypeRenderer_;
	std::vector<GameEngineRenderer*> GenderRenderer_;
	std::vector<GameEngineRenderer*> PokemonSkillTypeRenderer_[6]; // 플레이어는 1개의 포켓몬만 가지니 벡터의 벡터 >> 그냥 벡터로 변경시켰음
	std::vector<GameEngineRenderer*> PokemonSkillSelect_MiniPokemonRenderer_; // 포켓몬 아이콘 이미지 렌더러
	std::vector<GameEngineRenderer*> PokemonSkillSelect_TypeRenderer_; // 포켓몬 타입 이미지
	std::vector<GameEngineRenderer*> PokemonSkillSelect_SelectLineRenderer_[6]; // 스킬 선택했을때 빨간 외곽선



	//폰트
	std::vector<GameEngineContentFont*> LevelFonts_;
	std::vector< GameEngineContentFont*> FrameNameFonts_;
	std::vector< GameEngineContentFont*> NameFonts_;
	std::vector< GameEngineContentFont*> NumberFonts_;
	std::vector<GameEngineContentFont*> NatureFonts_;
	std::vector< GameEngineContentFont*> AllFonts_;
	std::vector<GameEngineContentFont*> CurHpFonts_;
	std::vector<GameEngineContentFont*> MaxHpFonts_;
	std::vector<GameEngineContentFont*> AttFonts_;
	std::vector<GameEngineContentFont*> DefFonts_;
	std::vector<GameEngineContentFont*> SpAttFonts_;
	std::vector<GameEngineContentFont*> SpDefFonts_;
	std::vector<GameEngineContentFont*> SpeedFonts_;
	std::vector<GameEngineContentFont*> CurExpFonts_;
	std::vector<GameEngineContentFont*> NextExpFonts_;
	std::vector<GameEngineContentFont*> AbilityFonts_;
	std::vector<GameEngineContentFont*> AbilityExplanationFonts_;
	std::vector<GameEngineContentFont*> SkillNameFonts_[6]; // 플레이어는 1개의 포켓몬만 가지니 벡터의 벡터 >> 그냥 벡터로 변경시켰음
	std::vector<GameEngineContentFont*> CurSkillPPFonts_[6]; // 플레이어는 1개의 포켓몬만 가지니 벡터의 벡터 >> 그냥 벡터로 변경시켰음
	std::vector<GameEngineContentFont*> MaxSkillPPFonts_[6]; // 플레이어는 1개의 포켓몬만 가지니 벡터의 벡터 >> 그냥 벡터로 변경시켰음
	std::vector<GameEngineContentFont*> SkillValueFonts_[6]; // 플레이어는 1개의 포켓몬만 가지니 벡터의 벡터 >> 그냥 벡터로 변경시켰음
	std::vector<GameEngineContentFont*> SkillAccFonts_[6]; // 플레이어는 1개의 포켓몬만 가지니 벡터의 벡터 >> 그냥 벡터로 변경시켰음
	std::vector<GameEngineContentFont*> SkillExplanationFonts_[6]; // 플레이어는 1개의 포켓몬만 가지니 벡터의 벡터 >> 그냥 벡터로 변경시켰음

	GameEngineContentFont* Owner_; //레드 이름
	GameEngineContentFont* IDNumber_;//ID 폰트
	GameEngineContentFont* Item_; //아이템 폰트

	//타입 스트링
	std::vector<std::string> TypeString_; //.bmp는 미포함

	//캐릭터 통통튀는거 구현
	float AccGravity_;
	float CurYPos_;
	bool IsJumpStart_;
	float JumpTime_;
	void PokemonJump();
	void PokemonJumpStart();
};

