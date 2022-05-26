#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν :
class TestActor : public GameEngineActor
{
public:
	// constrcuter destructer
	TestActor();
	~TestActor();

	// delete Function
	TestActor(const TestActor& _Other) = delete;
	TestActor(TestActor&& _Other) noexcept = delete;
	TestActor& operator=(const TestActor& _Other) = delete;
	TestActor& operator=(TestActor&& _Other) noexcept = delete;

protected:
	void Start();
	void Update();

private:

};

