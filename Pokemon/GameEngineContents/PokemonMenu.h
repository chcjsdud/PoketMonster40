#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineContentFont;
class PokemonInfo;
class PokemonMenu : public GameEngineActor
{
	enum class PokemonMenuType
	{
		SelectPokemon,
		SelectAction,
		Max
	};
public:
	PokemonMenu();
	~PokemonMenu();


	PokemonMenu(const PokemonMenu& _Other) = delete;
	PokemonMenu(const PokemonMenu&& _Other) noexcept = delete;
	PokemonMenu& operator=(const PokemonMenu& _Ohter) = delete;
	PokemonMenu& operator=(const PokemonMenu&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:

	//Fsm
	void ChangeState(PokemonMenuType _Type);
	void UpdateState();

	void SelectPokemonStart();
	void SelectPokemonUpdate();
	
	void SelectActionStart();
	void SelectActionUpdate();

	PokemonMenuType CurState_;

	void InitRenderer();
	void GetPlayerPokemon();
	void OnUI(); //UI가 켜질경우
	void ChangeHp(int _PokemonIndex, int _value);


	//폰트 
	std::list<GameEngineContentFont*> AllFonts_; //나중에 OffUI일때 모든 폰트 삭제하기
	std::vector<GameEngineContentFont*> CurHpFonts_; //나중에 OffUi할 때 모든 폰트 클리어하기
	std::vector<GameEngineContentFont*> SelectFonts_;

	GameEngineContentFont* DialogFont_;
	GameEngineContentFont* QuestionFont_;
	void InitFont();

	//렌더러
	GameEngineRenderer* BackgroundRenderer_;
	GameEngineRenderer* BoxRenderer_[6];
	GameEngineRenderer* DialogRenderer_;
	GameEngineRenderer* QuestionDialogRenderer_;
	GameEngineRenderer* SelectDialogRenderer_;
	GameEngineRenderer* CancelRenderer_;
	GameEngineRenderer* PokemonRenderer_[6];
	GameEngineRenderer* HpRenderer_[6];

	//포켓몬 아이콘 관련
	float CurTickTime_;
	bool IsJump_;
	void IconJump(GameEngineRenderer* _Render);
	void ResetJump();

	//----------------------------------------- UI 키입력 관련----------------------------------------------------
	//가지고 있는 포켓몬 수
	int PokemonNumber_;
	//현재 키가 가리키고 있는 순서
	int CurrentOrder_;
	//왼쪽 오른쪽 버튼을 눌렀을 때 기억하는 키 내용
	int RememberOrder_;
	// 포켓몬 리스트
	std::vector<PokemonInfo*> PokemonList_;

};

