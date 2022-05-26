#include "PokemonInfoManager.h"
#include "Pokemon.h"
#include "PokemonInfo.h"
#include "PokemonSkillInfo.h"
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
		std::map<std::string, PokemonSkillInfo*>::iterator StartIter = AllSkillInfoList_.begin();
		std::map<std::string, PokemonSkillInfo*>::iterator EndIter = AllSkillInfoList_.end();

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
		std::map<std::string, ItemInfo*>::iterator StartIter = AllItemInfoList_.begin();
		std::map<std::string, ItemInfo*>::iterator EndIter = AllItemInfoList_.end();

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
		PokemonSkillInfo* Tackle = CreateSkillInfo("Tackle", 10, 35, PokemonType::NORMAL, SkillType::Physical);
		PokemonSkillInfo* TailWhip = CreateSkillInfo("TailWhip", 10, 30, PokemonType::NORMAL, SkillType::Status);
		PokemonSkillInfo* Scratch = CreateSkillInfo("Scratch", 10, 35, PokemonType::NORMAL, SkillType::Physical);
		PokemonSkillInfo* Growl = CreateSkillInfo("Growl", 10, 40, PokemonType::NORMAL, SkillType::Status);

		//Tackle: 몸통박치기
		//CreateSkillInfo<Tackle>("Tackle", 10, 35, PokemonType::NORMAL, SkillType::Physical);
		////Tail Whip: 꼬리 흔들기 
		//CreateSkillInfo<Tackle>("TailWhip", 10, 30, PokemonType::NORMAL, SkillType::Status);
		////Scratch: 할퀴기
		//CreateSkillInfo<Tackle>("Scratch", 10, 35, PokemonType::NORMAL, SkillType::Physical);
		////Scratch: 울음소리 
		//CreateSkillInfo<Tackle>("Growl", 10, 40, PokemonType::NORMAL, SkillType::Status);
	}

	{
		//Charmander: 파이리
		PokemonInfo* CharmanderInfo = CreatePokemonInfo("Charmander", PokemonType::FIRE, 1, 10, 10, 15, 15, 5);
		//스킬 초기화
		CharmanderInfo->AddMySkill(FindSkillInfo("Scratch"));
		CharmanderInfo->AddMySkill(FindSkillInfo("Growl"));

		//Squirtle: 꼬부기
		PokemonInfo* SquirtleInfo = CreatePokemonInfo("Squirtle", PokemonType::WATER, 1, 10, 10, 15, 15, 5);
		SquirtleInfo->AddMySkill(FindSkillInfo("Tackle"));
		SquirtleInfo->AddMySkill(FindSkillInfo("TailWhip"));

		//Bulbasaur: 이상해씨
		PokemonInfo* BulbasaurInfo = CreatePokemonInfo("Bulbasaur", PokemonType::GRASS, 1, 10, 10, 15, 15, 5);
		BulbasaurInfo->AddMySkill(FindSkillInfo("Tackle"));
		BulbasaurInfo->AddMySkill(FindSkillInfo("Growl"));

		//Pidgey: 구구
		PokemonInfo* PidgeyInfo = CreatePokemonInfo("Pidgey", PokemonType::FLYING, 1, 10, 10, 15, 15, 5);
		PidgeyInfo->AddMySkill(FindSkillInfo("Tackle"));

		//Rattata: 꼬렛
		PokemonInfo* RattataInfo = CreatePokemonInfo("Rattata", PokemonType::NORMAL, 1, 10, 10, 15, 15, 5);
		RattataInfo->AddMySkill(FindSkillInfo("Tackle"));
		RattataInfo->AddMySkill(FindSkillInfo("TailWhip"));
	}

	{
		ItemInfo* MonsterBall = CreateItemInfo("Pokeball", 10, ItemType::BALL, "A Ball thrown to catch a Pokemon.\\It is designed in a capsule style.");
		ItemInfo* Potion = CreateItemInfo("Potion", 10, ItemType::ITEM, "A Potion is an item that\\heals 20 HP of a Pokemon.");
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

PokemonSkillInfo* PokemonInfoManager::FindSkillInfo(const std::string& _Key)
{
	std::string Key = GameEngineString::ToUpperReturn(_Key);

	std::map<std::string, PokemonSkillInfo*>::iterator FindIter = AllSkillInfoList_.find(Key);

	if (FindIter == AllSkillInfoList_.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

ItemInfo* PokemonInfoManager::FindItemInfo(const std::string& _Key)
{
	std::string Key = GameEngineString::ToUpperReturn(_Key);

	std::map<std::string, ItemInfo*>::iterator FindIter = AllItemInfoList_.find(Key);

	if (FindIter == AllItemInfoList_.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

Pokemon* PokemonInfoManager::CreatePokemon(const std::string& _Name)
{
	Pokemon* NewPokemon = new Pokemon();
	PokemonInfo* MyInfo = FindPokemonInfo(_Name);

	NewPokemon->SetInfo(MyInfo);

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
	NewPokemonInfo->SetGender(false);
	NewPokemonInfo->SetPokemonImage(_Key);

	AllPokemonInfoList_.insert(std::make_pair(_Key, NewPokemonInfo));

	return NewPokemonInfo;
}

PokemonSkillInfo* PokemonInfoManager::CreateSkillInfo(const std::string& _Key, int _Value, int _PP, PokemonType _Type, SkillType _SkillType)
{
	PokemonSkillInfo* NewSkill = new PokemonSkillInfo();
	std::string Key = GameEngineString::ToUpperReturn(_Key);

	NewSkill->SetName(Key);
	NewSkill->SetValue(_Value);
	NewSkill->SetPP(_PP);
	NewSkill->SetType(_Type);
	NewSkill->SetSkillType(_SkillType);

	AllSkillInfoList_.insert(std::make_pair(Key, NewSkill));

	return NewSkill;
}

PokemonSkill* PokemonInfoManager::CreatePokemonSkill(const std::string& _Name)
{
	PokemonSkill* NewPokemonSkill = new PokemonSkill();
	PokemonSkillInfo* MyInfo = FindSkillInfo(_Name);

	NewPokemonSkill->SetInfo(MyInfo);

	return NewPokemonSkill;
}

ItemInfo* PokemonInfoManager::CreateItemInfo(const std::string& _Key, int _Value, ItemType _Type, const std::string& _Desc)
{
	ItemInfo* NewItem = new ItemInfo();
	std::string Key = GameEngineString::ToUpperReturn(_Key);

	NewItem->SetName(Key);
	NewItem->SetValue(_Value);
	NewItem->SetDesc(_Desc);

	AllItemInfoList_.insert(std::make_pair(Key, NewItem));
	return NewItem;
}

Item* PokemonInfoManager::CreateItem(const std::string& _Name)
{
	Item* NewItem = new Item();
	ItemInfo* MyInfo = FindItemInfo(_Name);

	NewItem->SetInfo(MyInfo);

	return NewItem;
}



