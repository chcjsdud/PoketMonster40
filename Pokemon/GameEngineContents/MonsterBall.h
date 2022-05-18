#pragma once
#include "Item.h"

// Ό³Έν : 
class MonsterBall : public Item
{
public:
	// constrcuter destructer
	MonsterBall();
	~MonsterBall();

	// delete Function
	MonsterBall(const MonsterBall& _Other) = delete;
	MonsterBall(MonsterBall&& _Other) noexcept = delete;
	MonsterBall& operator=(const MonsterBall& _Other) = delete;
	MonsterBall& operator=(MonsterBall&& _Other) noexcept = delete;

protected:

private:

};

