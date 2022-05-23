#include "PokemonInfoManager.h"
#include "Pokemon.h"
#include "PokemonInfo.h"
#include "PokemonSkill.h"
#include "MonsterBall.h"
#include "Potion.h"
#include "Tackle.h"

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
		//Tackle: 몸통박치기
		CreateSkill<Tackle>("Tackle", 10, 35, PokemonType::NORMAL, SkillType::Physical);
		//Tail Whip: 꼬리 흔들기 
		CreateSkill<Tackle>("TailWhip", 10, 30, PokemonType::NORMAL, SkillType::Status);
		//Scratch: 할퀴기
		CreateSkill<Tackle>("Scratch", 10, 35, PokemonType::NORMAL, SkillType::Physical);
		//Scratch: 울음소리 
		CreateSkill<Tackle>("Growl", 10, 40, PokemonType::NORMAL, SkillType::Status);
	}

	{
		//Charmander: 파이리
		PokemonInfo* CharmanderInfo = CreatePokemonInfo("Charmander", PokemonType::FIRE, 1, 10, 10, 15, 15, 5);
		//스킬 초기화
		CharmanderInfo->AddMySkill(FindSkill("Scratch")); 
		CharmanderInfo->AddMySkill(FindSkill("Growl")); 

		//Squirtle: 꼬부기
		PokemonInfo* SquirtleInfo = CreatePokemonInfo("Squirtle", PokemonType::WATER, 1, 10, 10, 15, 15, 5);
		SquirtleInfo->AddMySkill(FindSkill("Tackle"));
		SquirtleInfo->AddMySkill(FindSkill("TailWhip"));

		//Bulbasaur: 이상해씨
		PokemonInfo* BulbasaurInfo = CreatePokemonInfo("Bulbasaur", PokemonType::GRASS, 1, 10, 10, 15, 15, 5);
		BulbasaurInfo->AddMySkill(FindSkill("Tackle"));
		BulbasaurInfo->AddMySkill(FindSkill("Growl"));

		//Pidgey: 구구
		PokemonInfo* PidgeyInfo = CreatePokemonInfo("Pidgey", PokemonType::FLYING, 1, 10, 10, 15, 15, 5);
		PidgeyInfo->AddMySkill(FindSkill("Tackle"));
		
		//Rattata: 꼬렛
		PokemonInfo* RattataInfo = CreatePokemonInfo("Rattata", PokemonType::NORMAL, 1, 10, 10, 15, 15, 5);
		RattataInfo->AddMySkill(FindSkill("Tackle"));
		RattataInfo->AddMySkill(FindSkill("TailWhip"));
	}
		
	{
		CreateItem<MonsterBall>("MonsterBall", 10, ItemType::BALL, "A Ball thrown to catch a Pokemon.\\It is designed in a capsule style.");
		CreateItem<Potion>("Potion", 10, ItemType::ITEM, "A Potion is an item that\\heals 20 HP of a Pokemon.");
	}
}

void PokemonInfoManager::Update()
{
	
}

PokemonInfo* PokemonInfoManager::FindPokemonInfo(const std::string& _Key)
{
	std::map<std::string, PokemonInfo*>::iterator FindIter = AllPokemonInfoList_.find(_Key);

	if (FindIter == AllPokemonInfoList_.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

PokemonSkill* PokemonInfoManager::FindSkill(const std::string& _Key)
{
	std::string Key = GameEngineString::ToUpperReturn(_Key);

	std::map<std::string, PokemonSkill*>::iterator FindIter = AllPokemonSkillList_.find(Key);

	if (FindIter == AllPokemonSkillList_.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

Item* PokemonInfoManager::FindItem(const std::string& _Key)
{
	std::string Key = GameEngineString::ToUpperReturn(_Key);

	std::map<std::string, Item*>::iterator FindIter = AllItemList_.find(Key);

	if (FindIter == AllItemList_.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

Pokemon* PokemonInfoManager::CreatePokemon(const std::string& _Name)
{
	Pokemon* NewPokemon = new Pokemon();
	PokemonInfo* MyInfo = FindPokemonInfo(_Name);

	NewPokemon->GetInfo()->SetName(_Name);
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
	NewPokemon->GetInfo()->SetPokemonImage(_Name);

	return NewPokemon;
}

PokemonInfo* PokemonInfoManager::CreatePokemonInfo(const std::string& _Key, PokemonType _Type, int _Lv, int _Att, int _Def, int _SpAtt, int _SpDef, int _Speed)
{
	PokemonInfo* NewPokemonInfo = new PokemonInfo();

	NewPokemonInfo->SetName(_Key);
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

	AllPokemonInfoList_.insert(std::make_pair(_Key, NewPokemonInfo));

	return NewPokemonInfo;
}



