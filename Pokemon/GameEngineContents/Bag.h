#pragma once
#include <GameEngine/GameEngineActor.h>

enum class BagType
{
	ITEM,
	KEYITEM,
	BALL
};

class Bag : public GameEngineActor
{
public:
	Bag();
	~Bag();

	Bag(const Bag& _Other) = delete;
	Bag(Bag&& _Other) noexcept = delete;
	Bag& operator=(const Bag& _Other) = delete;
	Bag& operator=(Bag&& _Other) noexcept = delete;

	void MoveBag();
	void ChangeBag();

protected:
	virtual void Start();
	virtual void Update();

private:
	BagType MyType_;

	class GameEngineRenderer* BagRedrerer_;
	GameEngineRenderer* BagName_;

	GameEngineRenderer* LeftArrow_;
	GameEngineRenderer* RightArrow_;
	GameEngineRenderer* UpArrow_;
	GameEngineRenderer* DownArrow_;

	int BagIndex_;
	float MoveTime_;

	bool IsMove_;
};

