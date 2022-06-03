#pragma once
#include <map>
#include <vector>
#include <string>
#include "ContentEnum.h"
#include <GameEngineBase/GameEngineString.h>

class ItemInfo;
class Pokemon;
class PokemonInfo;
class PokemonSkillInfo;
class PokemonInfoManager
{
	// ¿Â¡ﬂ«ı : Debug
	friend class BattleLevel;
	friend class Bag;	

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
	void Update() {}
	
	PokemonInfo* FindPokemonInfo(const std::string& _Key);
	PokemonSkillInfo* FindSkillInfo(const std::string& _Key);
	ItemInfo* FindItemInfo(const std::string& _Key);

	Pokemon* CreatePokemon(const std::string& _Name);
	void DestroyPokemon(int _Id);
	Pokemon* FindPokemon(int _Id);
	class PokemonSkill* CreatePokemonSkill(const std::string& _Name);
	class Item* CreateItem(const std::string& _Name);

protected:

private:
	static int PokemonId_;

	std::map<int, Pokemon*> AllPokemonList_;
	std::vector<PokemonSkill*> AllPokemonSkillList_;
	std::vector<Item*> AllItemList_;

	std::map<std::string, PokemonInfo*> AllPokemonInfoList_;
	std::map<std::string, PokemonSkillInfo*> AllSkillInfoList_;
	std::map<std::string, ItemInfo*> AllItemInfoList_;

	PokemonInfo* CreatePokemonInfo(const std::string& _Key, PokemonType _Type, int _Lv, int _Att, int _Def, int _SpAtt, int _SpDef, int _Speed);
	PokemonSkillInfo* CreateSkillInfo(const std::string& _Key, int _Value, int _PP, PokemonType _Type, SkillType _SkillType, const std::string& _Desc);
	ItemInfo* CreateItemInfo(const std::string& _Key, int _Value, ItemType _Type, const std::string& _Desc);

	void CreateRandomNature(PokemonInfo* _Pokemon);
};

