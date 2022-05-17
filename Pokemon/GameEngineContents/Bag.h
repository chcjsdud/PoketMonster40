#pragma once

// Ό³Έν :
class Bag
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

private:

};

