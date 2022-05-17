#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Bag : public GameEngineActor
{
public:
	// constrcuter destructer
	Bag();
	~Bag();

	// delete Function
	Bag(const Bag& _Other) = delete;
	Bag(Bag&& _Other) noexcept = delete;
	Bag& operator=(const Bag& _Other) = delete;
	Bag& operator=(Bag&& _Other) noexcept = delete;

protected:
	virtual void Start();
	virtual void Update();

	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel);
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel);

private:

};

