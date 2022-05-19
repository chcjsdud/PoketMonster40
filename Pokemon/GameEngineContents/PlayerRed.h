#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImage.h>

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
// 설명 :
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

protected:

private:
	float4			CameraPos_;
	RedDir			CurrentDir_;
	bool			WMenuUICheck_;
	std::string		AnimationName_;
	std::string		ChangeDirText_;

	GameEngineRenderer* RedRender_;

	// 타일맵 및 이동관련
	PokemonTileMap* CurrentTileMap_;
	float4 CurrentTilePos_;

	GameEngineRenderer* WMenuUIRender_;
	GameEngineRenderer* WMenuArrowRender_;
	RedState CurrentState_;

	void Start() override;
	void Update() override;
	void Render() override;

	void PlayerSetMove(float4 _Value);
	void PlayerMoveTile(int _X, int _Y);

	void Camera();
	void WMenuUISelect();

	bool IsMoveKey();
	void IsWMenuKey();


	// FSM
	float AnimTimer_;

	void IdleUpdate();
	void WalkUpdate();
	void RunUpdate();

	void IdleStart();
	void WalkStart();
	void RunStart();
};
