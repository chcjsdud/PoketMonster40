#pragma once
#include <GameEngine/GameEngineLevel.h>

class UITestLevel : public GameEngineLevel
{
public:
	UITestLevel();
	~UITestLevel();


	UITestLevel(const UITestLevel& _Other) = delete;
	UITestLevel(const UITestLevel&& _Other) noexcept = delete;
	UITestLevel& operator=(const UITestLevel& _Ohter) = delete;
	UITestLevel& operator=(const UITestLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
};

