#pragma once
#include "ItemInfo.h"

class ItemInfo;
class Item
{
public:
	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

	inline ItemInfo* GetInfo()
	{
		return &MyInfo_;
	}

protected:
	virtual void Use() {}

private:
	ItemInfo MyInfo_;
};

