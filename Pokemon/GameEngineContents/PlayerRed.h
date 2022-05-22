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

class Pokemon;
class PokemonTileMap;
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

	void ChangeState(RedState _State);
	void StateUpdate();
	void DirAnimationCheck();

	void FadeIn();
	void FadeOut();
	void FadeRL();

protected:

private:
	float4			CameraPos_;
	float4			StartPos_;
	float4			GoalPos_;
	RedDir			CurrentDir_;
	bool			WMenuUICheck_;
	std::string		AnimationName_;
	std::string		ChangeDirText_;

	GameEngineRenderer* RedRender_;
	GameEngineRenderer* ShadowRender_;
	GameEngineRenderer* FadeRender_;
	GameEngineRenderer* FadeRightRender_;
	GameEngineRenderer* FadeLeftRender_;
	bool IsFadeIn_;
	bool IsFadeOut_;
	bool IsFadeRL_;
	bool IsFadeRLCheck_;
	float LerpX_;
	float LerpY_;
	float LerpTime_;
	float FadeTime_;
	UINT Alpha_;
	
	// 타일맵 및 이동관련
	PokemonTileMap* CurrentTileMap_;
	PokemonTileMap* NextTileMap_;
	float4 CurrentTilePos_;
	float4 NextTilePos_;
	bool IsMove_;
	bool IsJump_;

	GameEngineRenderer* WMenuUIRender_;
	GameEngineRenderer* WMenuArrowRender_;
	RedState CurrentState_;

	//레드의 포켓몬과 아이템
	std::vector<Pokemon*> MyPokemonList_;
	std::vector<std::string> MyItemList_;

	void Start() override;
	void Update() override;
	void Render() override;

	void PlayerSetMove(float4 _Value);
	bool PlayerMoveTileCheck(int _X, int _Y);
	void MoveTile(PokemonTileMap& _Tile, float4 _Pos);
	
	void Camera();
	void WMenuUISelect();

	bool IsMoveKey();
	void IsWMenuKey();

	void MoveAnim();

	// 상호작용
	void InteractionUpdate();
	bool InteractTileCheck(int _X, int _Y, RedDir _Dir);

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
};
