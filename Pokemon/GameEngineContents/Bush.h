#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Bush : public GameEngineActor
{
public:
	// constrcuter destructer
	Bush();
	~Bush();

	// delete Function
	Bush(const Bush& _Other) = delete;
	Bush(Bush&& _Other) noexcept = delete;
	Bush& operator=(const Bush& _Other) = delete;
	Bush& operator=(Bush&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* Renderer_;

	void Start() override;
};

