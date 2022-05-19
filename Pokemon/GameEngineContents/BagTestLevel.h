#pragma once
#include <GameEngine/GameEngineLevel.h>

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

private:
	class Bag* Bag_;

};

