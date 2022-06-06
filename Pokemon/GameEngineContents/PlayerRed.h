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

	void FadeIn();
	void FadeOut();
	void FadeRL();

	inline void SetInteraction(const bool _Value)
	{
		IsInteraction_ = _Value;
	}

	inline std::vector<Pokemon*>& GetPokemonList()
	{
		return MyPokemonList_;
	}

protected:

private:
	float4			CameraPos_;
	float4			StartPos_;
	float4			GoalPos_;
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

	GameEngineRenderer* WMenuUIRender_;
	GameEngineRenderer* WMenuArrowRender_;
	RedState CurrentState_;

	//레드의 포켓몬과 아이템
	std::vector<Pokemon*> MyPokemonList_;
	std::vector<class Item*> MyItemList_;

	void Start() override;
	void Update() override;
	void Render() override;

	void PlayerSetMove(float4 _Value);
	bool PlayerMoveTileCheck(int _X, int _Y);
	
	void Camera();
	void WMenuUISelect();

	bool IsMoveKey();
	void IsWMenuKey();

	void MoveAnim();
	bool CanMove();

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

	void UIUpdate(); 
	void InitMyPokemon();
};
