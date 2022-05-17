#pragma once
#include <map>
#include <string>

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

	Pokemon* CreatePokemon();
	PokemonSkill* CreateSkill();
	Item* CreateItem();
};

