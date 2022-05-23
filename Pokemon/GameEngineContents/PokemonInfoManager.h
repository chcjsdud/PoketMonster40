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
	
	PokemonInfo* FindPokemonInfo(const std::string& _Key);
	PokemonSkill* FindSkill(const std::string& _Key);
	Item* FindItem(const std::string& _Key);

	template<typename ItemKind>
	Item* CreateItem(const std::string& _Key, int _Value, ItemType _Type, const std::string& _Desc)
	{
		Item* NewItem = new ItemKind();
		std::string Key = GameEngineString::ToUpperReturn(_Key);

		NewItem->SetName(Key);
		NewItem->SetValue(_Value);
		NewItem->SetDesc(_Desc);

		AllItemList_.insert(std::make_pair(Key, NewItem));
		return NewItem;
	}

	template<typename SkillKind>
	PokemonSkill* CreateSkill(const std::string& _Key, int _Value, int _PP, PokemonType _Type, SkillType _SkillType)
	{
		PokemonSkill* NewSkill = new SkillKind();
		std::string Key = GameEngineString::ToUpperReturn(_Key);

		NewSkill->SetName(Key);
		NewSkill->SetValue(_Value);
		NewSkill->SetPP(_PP);
		NewSkill->SetType(_Type);
		NewSkill->SetSkillType(_SkillType);

		AllPokemonSkillList_.insert(std::make_pair(Key, NewSkill));

		return NewSkill;
	}

protected:

private:
	std::map<std::string, PokemonInfo*> AllPokemonInfoList_;
	std::map<std::string, PokemonSkill*> AllPokemonSkillList_;
	std::map<std::string, Item*> AllItemList_;

	Pokemon* CreatePokemon(const std::string& _Name);
	PokemonInfo* CreatePokemonInfo(const std::string& _Key, PokemonType _Type, int _Lv, int _Att, int _Def, int _SpAtt, int _SpDef, int _Speed);
};

