#include "PokemonInfoManager.h"
#include "Pokemon.h"
#include "PokemonInfo.h"
#include "PokemonSkill.h"
#include "MonsterBall.h"
#include "Potion.h"

PokemonInfoManager* PokemonInfoManager::Inst_ = new PokemonInfoManager();

PokemonInfoManager::PokemonInfoManager() 
{
}

PokemonInfoManager::~PokemonInfoManager() 
{
	{
		std::map<std::string, PokemonInfo*>::iterator StartIter = AllPokemonInfoList_.begin();
		std::map<std::string, PokemonInfo*>::iterator EndIter = AllPokemonInfoList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr != StartIter->second)
			{
				delete StartIter->second;
				StartIter->second = nullptr;
			}
		}
	}

	{
		std::map<std::string, PokemonSkill*>::iterator StartIter = AllPokemonSkillList_.begin();
		std::map<std::string, PokemonSkill*>::iterator EndIter = AllPokemonSkillList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr != StartIter->second)
			{
				delete StartIter->second;
				StartIter->second = nullptr;
			}
		}
	}

	{
		std::map<std::string, Item*>::iterator StartIter = AllItemList_.begin();
		std::map<std::string, Item*>::iterator EndIter = AllItemList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr != StartIter->second)
			{
				delete StartIter->second;
				StartIter->second = nullptr;
			}
		}
	}
}

void PokemonInfoManager::Reset()
{
	{
		//Charmander: 颇捞府
		CreatePokemonInfo("Charmander", PokemonType::FIRE, 1, 10, 10, 15, 15, 5);
		//Squirtle: 部何扁
		CreatePokemonInfo("Squirtle", PokemonType::WATER, 1, 10, 10, 15, 15, 5);
		//Bulbasaur: 捞惑秦揪
		CreatePokemonInfo("Bulbasaur", PokemonType::GRASS, 1, 10, 10, 15, 15, 5);
		//Pidgey: 备备
		CreatePokemonInfo("Pidgey", PokemonType::FLYING, 1, 10, 10, 15, 15, 5);
		//Rattata: 部房
		CreatePokemonInfo("Rattata", PokemonType::NORMAL, 1, 10, 10, 15, 15, 5);
	}

	{
		//Tackle: 个烹冠摹扁
		CreateSkill("Tackle", 10, PokemonType::NORMAL, SkillType::Attack);
		//Tail Whip: 部府 如甸扁 
		CreateSkill("TailWhip", 10, PokemonType::NORMAL, SkillType::Debuff);
		//Scratch: 且柠扁
		CreateSkill("Scratch", 10, PokemonType::NORMAL, SkillType::Attack);
		//Scratch: 匡澜家府 
		CreateSkill("Growl", 10, PokemonType::NORMAL, SkillType::Debuff);
	}
		
	{
		CreateItem<MonsterBall>("MonsterBall", 10);
		CreateItem<Potion>("Potion", 10);
	}
}

void PokemonInfoManager::Update()
{
	
}

PokemonInfo* PokemonInfoManager::FindPokemonInfo(const std::string _Key)
{
	std::string Key = GameEngineString::ToUpperReturn(_Key);

	std::map<std::string, PokemonInfo*>::iterator FindIter = AllPokemonInfoList_.find(Key);

	if (FindIter == AllPokemonInfoList_.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

PokemonSkill* PokemonInfoManager::FindSkill(std::string _Key)
{
	std::string Key = GameEngineString::ToUpperReturn(_Key);

	std::map<std::string, PokemonSkill*>::iterator FindIter = AllPokemonSkillList_.find(Key);

	if (FindIter == AllPokemonSkillList_.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

Item* PokemonInfoManager::FindItem(std::string _Key)
{
	std::string Key = GameEngineString::ToUpperReturn(_Key);

	std::map<std::string, Item*>::iterator FindIter = AllItemList_.find(Key);

	if (FindIter == AllItemList_.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

Pokemon* PokemonInfoManager::CreatePokemon(const std::string _Name)
{
	std::string Key = GameEngineString::ToUpperReturn(_Name);

	Pokemon* NewPokemon = new Pokemon();
	PokemonInfo* MyInfo = FindPokemonInfo(_Name);

	NewPokemon->GetInfo()->SetName(Key);
	NewPokemon->GetInfo()->SetMyType(MyInfo->GetMyType());
	NewPokemon->GetInfo()->SetStatusEffect(MyInfo->GetStatusEffect());
	NewPokemon->GetInfo()->SetMyLevel(MyInfo->GetMyLevel());
	NewPokemon->GetInfo()->SetMyMaxLevel(MyInfo->GetMyMaxLevel());
	NewPokemon->GetInfo()->SetHp(MyInfo->GetHp());
	NewPokemon->GetInfo()->SetMaxHp(MyInfo->GetMaxHp());
	NewPokemon->GetInfo()->SetExp(MyInfo->GetExp());
	NewPokemon->GetInfo()->SetMaxExp(MyInfo->GetMaxExp());
	NewPokemon->GetInfo()->SetAtt(MyInfo->GetAtt());
	NewPokemon->GetInfo()->SetDef(MyInfo->GetDef());
	NewPokemon->GetInfo()->SetSpAtt(MyInfo->GetSpAtt());
	NewPokemon->GetInfo()->SetSpDef(MyInfo->GetSpDef());
	NewPokemon->GetInfo()->SetSpeed(MyInfo->GetSpeed());
	NewPokemon->GetInfo()->SetIsPlayer(MyInfo->GetIsPlayer());
	NewPokemon->GetInfo()->SetIsGender(MyInfo->GetGender());
	NewPokemon->GetInfo()->SetPokemonImage(Key);

	return NewPokemon;
}

PokemonInfo* PokemonInfoManager::CreatePokemonInfo(const std::string _Key, PokemonType _Type, int _Lv, int _Att, int _Def, int _SpAtt, int _SpDef, int _Speed)
{
	PokemonInfo* NewPokemonInfo = new PokemonInfo();

	std::string Key = GameEngineString::ToUpperReturn(_Key);

	NewPokemonInfo->SetName(Key);
	NewPokemonInfo->SetMyType(_Type);
	NewPokemonInfo->SetStatusEffect(StatusEffect::NONE);
	NewPokemonInfo->SetMyLevel(_Lv);
	NewPokemonInfo->SetMyMaxLevel(100);
	NewPokemonInfo->SetHp(100);
	NewPokemonInfo->SetMaxHp(100);
	NewPokemonInfo->SetExp(0);
	NewPokemonInfo->SetMaxExp(100);
	NewPokemonInfo->SetAtt(_Att);
	NewPokemonInfo->SetDef(_Def);
	NewPokemonInfo->SetSpAtt(_SpAtt);
	NewPokemonInfo->SetSpDef(_SpDef);
	NewPokemonInfo->SetSpeed(_Speed);
	NewPokemonInfo->SetIsPlayer(false);
	NewPokemonInfo->SetIsGender(false);
	NewPokemonInfo->SetPokemonImage(_Key);

	AllPokemonInfoList_.insert(std::make_pair(Key, NewPokemonInfo));

	return NewPokemonInfo;
}

PokemonSkill* PokemonInfoManager::CreateSkill(const std::string _Key, int _Value, PokemonType _Type, SkillType _SkillType)
{
	PokemonSkill* NewSkill = new PokemonSkill();
	std::string Key = GameEngineString::ToUpperReturn(_Key);

	NewSkill->SetName(Key);
	NewSkill->SetValue(_Value);
	NewSkill->SetType(_Type);
	NewSkill->SetSkillType(_SkillType);
	//NewSkill->SetMyEffect(NewSkill->CreateRenderer("Tackle.bmp"));

	AllPokemonSkillList_.insert(std::make_pair(Key, NewSkill));

	return NewSkill;
}

