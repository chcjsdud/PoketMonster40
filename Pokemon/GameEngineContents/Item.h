#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngine/GameEngineImage.h>
#include <string>
#include "ContentEnum.h"

class Item : public GameEngineNameObject
{
public:
	Item();
	virtual ~Item();

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

	inline void SetType(ItemType _Type)
	{
		Type_ = _Type;
	}

	inline ItemType GetType()
	{
		return Type_;
	}

	inline void SetDesc(const std::string& _Desc)
	{
		Desc_ = _Desc;
	}

	inline std::string& GetDesc()
	{
		return Desc_;
	}

protected:
	virtual void Use() = 0;

private:
	int Value_; //상처약이라면 회복될 수치
	ItemType Type_;
	std::string Desc_;
};

