#pragma once
#include <GameEngine/GameEngineActor.h>

class Bag : public GameEngineActor
{
public:
	Bag();
	~Bag();

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

