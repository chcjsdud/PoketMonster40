#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImage.h>
#include <vector>

enum class RedState
{
	Idle,
	Walk,
	Run,

	Max
};
enum class RedDir
{
	Up,
	Down,
	Left,
	Right,
};

class Bush;
class Pokemon;
class PokemonTileMap;
class GameEngineCollision;
class PlayerRed : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerRed();
	~PlayerRed();

	// delete Function
	PlayerRed(const PlayerRed& _Other) = delete;
	PlayerRed(PlayerRed&& _Other) noexcept = delete;
	PlayerRed& operator=(const PlayerRed& _Other) = delete;
	PlayerRed& operator=(PlayerRed&& _Other) noexcept = delete;

	static PlayerRed* MainRed_;
	static bool	WMenuUICheck_;

	void ChangeState(RedState _State);
	void StateUpdate();
	void DirAnimationCheck();
	void RedMoveControll(RedDir _Dir, int _Count);

	void FadeIn();
	void FadeOut();
	void FadeRL();

	float NextDirMoveTimer_;
	int Count_;
	
	inline void SetInteraction(const bool _Value)
	{
		IsInteraction_ = _Value;
	}

	inline void SetFadeIn(const bool _Value)
	{
		IsFadeIn_ = _Value;
	}

	inline void SetOakCall(const bool _Value)
	{
		IsOakCall_ = _Value;
	}

	inline void SetRedMoveCheck(const bool _Value)
	{
		IsRedMoveCheck_ = _Value;
	}

	inline void SetRedMoveEnd(const bool _Value)
	{
		IsRedMoveEndCheck_ = _Value;
	}

	inline void SetControllOn(const bool _Value)
	{
		IsControllOnCheck_ = _Value;
	}

	inline void SetGreenBattle(const bool _Value)
	{
		IsGreenBattleCheck_ = _Value;
	}
	
	inline void SetCurrentTileMap(PokemonTileMap* _Value)
	{
		CurrentTileMap_ = _Value;
	}

	inline std::vector<Pokemon*>& GetPokemonList()
	{
		return MyPokemonList_;
	}

	inline void AddPokemon(Pokemon* _Pokemon)
	{
		if (nullptr == _Pokemon)
		{
			return;
		}

		MyPokemonList_.push_back(_Pokemon);
	}

	inline std::vector<class Item*>& GetItemList()
	{
		return MyItemList_;
	}

	inline float4 GetRedCurrentIndex()
	{
		return RedCurrentIndex_;
	}

	inline float4 GetCurrentTilePos()
	{
		return CurrentTilePos_;
	}

	inline bool GetStartEvent()
	{
		return IsStartEvent_;
	}

	inline bool GetOakCall()
	{
		return IsOakCall_;
	}

	inline bool GetRedMoveEnd()
	{
		return IsRedMoveEndCheck_;
	}

	inline bool GetGreenBattle()
	{
		return IsGreenBattleCheck_;
	}

	inline int GetMoney()
	{
		return Money_;
	}

	inline void SetMoney(int _Money)
	{
		Money_ = _Money;
	}

	inline GameEngineActor* GetChildUI()
	{
		return ChildUI_;
	}

	inline void SetChildUI(GameEngineActor* _Child)
	{
		ChildUI_ = _Child;
	}

	void PopUpPokemonPreview(int _Index);

protected:

private:
	float4			CameraPos_;
	float4			StartPos_;
	float4			GoalPos_;
	float4			RedCurrentIndex_;
	float4			RedMoveDir_;
	RedDir			CurrentDir_;
	//bool			WMenuUICheck_;
	std::string		AnimationName_;
	std::string		ChangeDirText_;

	GameEngineRenderer*		RedRender_;
	GameEngineRenderer*		ShadowRender_;
	GameEngineRenderer*		FadeRender_;
	GameEngineRenderer*		FadeRightRender_;
	GameEngineRenderer*		FadeLeftRender_;
	GameEngineCollision*	RedCollision_;
	GameEngineCollision*	RedFrontCollision_;
	bool IsFadeIn_;
	bool IsFadeOut_;
	bool IsFadeRL_;
	bool IsFadeRLCheck_;
	bool IsStartEvent_;
	bool IsRedMoveCheck_;
	bool IsRedMoveEndCheck_;
	bool IsControllOnCheck_;
	bool IsGreenBattleCheck_;
	bool NPC5Check_;
	float LerpX_;
	float LerpY_;
	float LerpTime_;
	float FadeTime_;
	float Alpha_;
	
	// 타일맵 및 이동관련
	PokemonTileMap* BeforeTileMap_;
	PokemonTileMap* CurrentTileMap_;
	PokemonTileMap* NextTileMap_;
	float4 CurrentTilePos_;
	float4 NextTilePos_;
	bool IsMove_;
	bool IsJump_;
	bool IsInteraction_;
	bool IsBush_;
	bool IsBushEventReady_;
	bool IsDebugRun_;
	bool IsPokemonMenuOn_;
	bool IsOakCall_;
	bool IsOakCallCheck_;

	GameEngineRenderer* WMenuArrowRender_;
	RedState CurrentState_;

	//레드의 포켓몬과 아이템
	std::vector<Pokemon*> MyPokemonList_;
	std::vector<class Item*> MyItemList_;

	void Start() override;
	void Update() override;
	void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	void PlayerSetMove(float4 _Value);
	bool PlayerMoveTileCheck(int _X, int _Y);
	
	void Camera();
	//void WMenuUISelect();

	bool IsMoveKey();

	void MoveAnim();
	bool CanMove();

	void OakCall();
	
	// 상호작용
	void InteractionUpdate();
	bool InteractionNPC();
	bool InteractTileCheck(int _X, int _Y, RedDir _Dir);

	// 수풀
	Bush* BushActor_;
	bool BushTileCheck(int _X, int _Y);

	// 사운드
	void SoundTileCheck();

	// FSM
	float AnimTimer_;
	float NextMoveTime_;
	float MoveTimer_;

	void IdleUpdate();
	void WalkUpdate();
	void RunUpdate();

	void IdleStart();
	void WalkStart();
	void RunStart();


	//--------------------------------------------------------------UI-------------------------------------------------------------------------------------------
private:
	GameEngineActor* ChildUI_;
	class FadeActor* FadeActor_;

	int Money_; //플레이어 돈. 상점에 필요

	GameEngineRenderer* PokemonPreview_; //스타팅 포켓몬 전용 UI

	void UIUpdate(); 
	void InitMyPokemon();

	bool YesOrNOpen_;

	//void PopUpPokemonPreview(int _Index);
};
