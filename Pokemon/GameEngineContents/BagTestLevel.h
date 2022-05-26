#pragma once
#include <GameEngine/GameEngineLevel.h>

class GameEngineRenderer;
class BagTestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BagTestLevel();
	~BagTestLevel();

	// delete Function
	BagTestLevel(const BagTestLevel& _Other) = delete;
	BagTestLevel(BagTestLevel&& _Other) noexcept = delete;
	BagTestLevel& operator=(const BagTestLevel& _Other) = delete;
	BagTestLevel& operator=(BagTestLevel&& _Other) noexcept = delete;

protected:
	void Loading();
	void Update();

	void LevelChangeStart(GameEngineLevel* _PrevLevel);
	void LevelChangeEnd(GameEngineLevel* _PrevLevel);

private:
	class Bag* Bag_;
	GameEngineRenderer* Renderer_;
};

