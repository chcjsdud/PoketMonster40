#pragma once
#include <GameEngine/GameEngineActor.h>

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

protected:

private:
	float4 CameraPos_;

	GameEngineRenderer* RedRender_;
	
	void Start() override;
	void Update() override;
	void Render() override;

	void Camera();
};

