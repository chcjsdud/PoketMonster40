#pragma once
#include <GameEngine/GameEngineActor.h>

class FadeActor;
class GameEngineContentFont;
class PokemonInfo;
class Item;
class PokemonMenu : public GameEngineActor
{
	enum class PokemonMenuType
	{
		SelectPokemon,
		SelectAction,
		SelectSwitch,
		Switching,
		OpeningChildUI,
		UsingPotion,
		Max
	};

	enum class ChildUIType
	{
		None,
		PokemonSummaryMenu,
		Max
	};
public:
	PokemonMenu();
	~PokemonMenu();


	PokemonMenu(const PokemonMenu& _Other) = delete;
	PokemonMenu(const PokemonMenu&& _Other) noexcept = delete;
	PokemonMenu& operator=(const PokemonMenu& _Ohter) = delete;
	PokemonMenu& operator=(const PokemonMenu&& _Other) noexcept = delete;

	void InitPokemonMenu(Item* _Item = nullptr);
	void DestroyPokemonMenu();

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	void UpdateRenderInfo();
	//Fsm
	void ChangeState(PokemonMenuType _Type);
	void UpdateState();

	void SelectPokemonStart();
	void SelectPokemonUpdate();
	
	void SelectActionStart();
	void SelectActionUpdate();

	void SelectSwitchStart();
	void SelectSwitchUpdate();

	void SwitchingStart();
	void SwitchingUpdate();

	void OpeningChildUIStart();
	void OpeningChildUIUpdate();

	void UsingPotionStart();
	void UsingPotionUpdate();

	PokemonMenuType CurState_;

	void InitRenderer();
	void GetPlayerPokemon();
	void OnUI(); //UI가 켜질경우
	void ChangeHp(int _PokemonIndex, int _value);


	//폰트 
	std::vector<GameEngineContentFont*> CurHpFonts_; //나중에 OffUi할 때 모든 폰트 클리어하기
	std::vector< GameEngineContentFont*> PokemonNameFonts_;
	std::vector< GameEngineContentFont*> PokemonLevelFonts_;
	std::vector< GameEngineContentFont*> MaxHpFonts_;

	GameEngineContentFont* DialogFont_;
	GameEngineContentFont* SwitchFont_;
	GameEngineContentFont* QuestionFont_;
	GameEngineContentFont* UsingPotionFont_;
	void InitFont();

	//렌더러
	GameEngineRenderer* MenuArrowRenderer_;
	GameEngineRenderer* BackgroundRenderer_;
	GameEngineRenderer* BoxRenderer_[6];
	GameEngineRenderer* DialogRenderer_;
	GameEngineRenderer* QuestionDialogRenderer_;
	GameEngineRenderer* SelectDialogRenderer_;
	GameEngineRenderer* CancelRenderer_;
	GameEngineRenderer* UsingPotionBoxRenderer_;
	std::vector<GameEngineRenderer*> PokemonRenderer_;
	GameEngineRenderer* HpRenderer_[6];
	GameEngineRenderer* GenderRenderer_[6];

	//Switching 연출관련
	float SwitchingTime_;
	bool IsSwitchingStart_;
	bool IsSwitchingTurn_;
	void MoveAllRenderer(int _index, float _Speed);

	//포켓몬 아이콘 관련
	float CurTickTime_;
	bool CanJump_[6]; //On일경우 점프를 반복
	void IconJump();
	void IconJumpOn(int _PokemonOrder);
	void IconJumpOff(int _PokemonOrder);

	//자식 UI로 이동 관련
	GameEngineActor* ChildUIActor_;
	ChildUIType CurChildUIType_;
	PokemonMenuType PrevMenuType_;

	//On관련
	bool IsOn_; // Init함수가 호출되야 업데이트를 시작하게 만든다

	//FadeOut관련
	FadeActor* FadeActor_;


	//----------------------------------------- UI 키입력 관련----------------------------------------------------
	//가지고 있는 포켓몬 수
	int PokemonNumber_;
	//현재 키가 가리키고 있는 순서 < 포켓몬의
	int CurrentOrder_;
	//현재 SelectAction에서 순서
	int SelectActionOrder_;
	//왼쪽 오른쪽 버튼을 눌렀을 때 기억하는 키 내용
	int RememberOrder_;

	//바꿀 포켓몬 넘버
	int ChangePokemonNumber_1;
	int ChangePokemonNumber_2;

	// 포켓몬 리스트
	std::vector<PokemonInfo*> PokemonList_;

	float MenuTime_;


	//--------------------------------------- 상처약 이벤트 관련-------------------------------------------------------------

	bool IsItemMode_; //true : 상처약 사용 모드, false : 일반 모드
	float UsingPotionTime_;
	int PotionValue_;
};

