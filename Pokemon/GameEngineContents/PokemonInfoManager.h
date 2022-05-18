#pragma once
#include <map>
#include <string>
#include "ContentEnum.h"

class Item;
class Pokemon;
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

protected:

private:
	std::map<std::string, Pokemon*> AllPokemonList_;
	std::map<std::string, PokemonSkill*> AllPokemonSkillList_;
	std::map<std::string, Item*> AllItemList_;

	Pokemon* CreatePokemon(std::string _Key, PokemonType _Type, int _Lv, int _Att, int _Def, int _SpAtt, int _SpDef, int _Speed);
	PokemonSkill* CreateSkill();
	Item* CreateItem();
};

