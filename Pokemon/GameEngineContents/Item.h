#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngine/GameEngineImage.h>
#include <string>

class Item : public GameEngineNameObject
{
public:
	Item();
	~Item();

	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

	inline void SetValue(int _Value)
	{
		Value_ = _Value;
	}

	inline int GetValue()
	{
		return Value_;
	}

	void SetItemImage(const std::string& _Name);

protected:

private:
	int Value_; //상처약이라면 회복될 수치
	GameEngineImage* MyIcon_;
};

