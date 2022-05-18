#pragma once
#include <GameEngine/GameEngineActor.h>

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
// Ό³Έν :
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
	std::string		AnimationName_;
	std::string		ChangeDirText_;

	GameEngineRenderer* RedRender_;
	RedState CurrentState_;

	void Start() override;
	void Update() override;
	void Render() override;

	void Camera();

	bool IsMoveKey();

	void IdleUpdate();
	void WalkUpdate();
	void RunUpdate();

	void IdleStart();
	void WalkStart();
	void RunStart();
};

