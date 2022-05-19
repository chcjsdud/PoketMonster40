#pragma once
#include <map>
#include <string>
#include "ContentEnum.h"
#include <GameEngineBase/GameEngineString.h>

class Item;
class Pokemon;
class PokemonInfo;
class PokemonSkill;
class PokemonInfoManager
{
private:
	static PokemonInfoManager* Inst_;

public:
	inline static PokemonInfoManager& GetInst()
	{
		return *Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

public:
	PokemonInfoManager();
	~PokemonInfoManager();

	PokemonInfoManager(const PokemonInfoManager& _Other) = delete;
	PokemonInfoManager(PokemonInfoManager&& _Other) noexcept = delete;
	PokemonInfoManager& operator=(const PokemonInfoManager& _Other) = delete;
	PokemonInfoManager& operator=(PokemonInfoManager&& _Other) noexcept = delete;

	void Reset();
	void Update();
	
	PokemonInfo* FindPokemonInfo(std::string _Key);
	PokemonSkill* FindSkill(std::string _Key);
	Item* FindItem(std::string _Key);

	template<typename ItemType>
	Item* CreateItem(const std::string _Key, int _Value)
	{
		Item* NewItem = new ItemType();
		std::string Key = GameEngineString::ToUpperReturn(_Key);

		NewItem->SetName(Key);
		NewItem->SetValue(_Value);
		NewItem->SetItemImage(Key);

		AllItemList_.insert(std::make_pair(Key, NewItem));
		return NewItem;
	}

protected:

private:
	std::map<std::string, PokemonInfo*> AllPokemonInfoList_;
	std::map<std::string, PokemonSkill*> AllPokemonSkillList_;
	std::map<std::string, Item*> AllItemList_;

	Pokemon* CreatePokemon(const std::string _Name);
	PokemonInfo* CreatePokemonInfo(const std::string _Key, PokemonType _Type, int _Lv, int _Att, int _Def, int _SpAtt, int _SpDef, int _Speed);
	PokemonSkill* CreateSkill(const std::string _Key, int Value, int _PP, PokemonType _Type, SkillType _SkillType);
};

