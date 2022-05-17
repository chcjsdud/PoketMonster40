#pragma once

// Ό³Έν :
class Test
{
public:
	// constrcuter destructer
	Test();
	~Test();

	// delete Function
	Test(const Test& _Other) = delete;
	Test(Test&& _Other) noexcept = delete;
	Test& operator=(const Test& _Other) = delete;
	Test& operator=(Test&& _Other) noexcept = delete;

protected:

private:

};

