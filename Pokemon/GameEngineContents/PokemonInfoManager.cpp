#include "PokemonInfoManager.h"
#include "Pokemon.h"
#include "PokemonInfo.h"
#include "PokemonSkillInfo.h"
#include "MonsterBall.h"
#include "Potion.h"
#include "Tackle.h"
#include "ContentEnum.h"
#include "GameEngineBase/GameEngineRandom.h"


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
		//Tackle: 몸통박치기
		PokemonSkillInfo* Tackle = CreateSkillInfo("Tackle", 10, 35, PokemonType::NORMAL, SkillType::Physical, "A physical attack in which the user charges,\\full body, into the foe.");
		////Tail Whip: 꼬리 흔들기 
		PokemonSkillInfo* TailWhip = CreateSkillInfo("TailWhip", 10, 30, PokemonType::NORMAL, SkillType::Status, "Lowers the opponent's Pokémon's Defense by 1 stage.");
		////Scratch: 할퀴기
		PokemonSkillInfo* Scratch = CreateSkillInfo("Scratch", 10, 35, PokemonType::NORMAL, SkillType::Physical, "Hard, pointed, and sharp claws rake the foe.");
		////Scratch: 울음소리 
		PokemonSkillInfo* Growl = CreateSkillInfo("Growl", 10, 40, PokemonType::NORMAL, SkillType::Status, "The user growls in a cute way, making the foe lower its Attack. stat.");
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
	NewPokemon->GetInfo()->SetGender(MyInfo->GetGender());
	NewPokemon->GetInfo()->SetSkill(MyInfo->GetSkill()); //깊은 복사로 바꿔야함!!!!
	NewPokemon->GetInfo()->SetPokemonImage(_Name); 

	CreateRandomNature(MyInfo);

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

void PokemonInfoManager::CreateRandomNature(PokemonInfo* _Pokemon)
{
	int RandomNature = GameEngineRandom::GetInst_->RandomInt(0, static_cast<int>(PokemonNature::End));

	switch (RandomNature)
	{
	case static_cast<int>(PokemonNature::Quirky):
		_Pokemon->SetNature("Quirky");
		break;
	case static_cast<int>(PokemonNature::Bold):
		_Pokemon->SetNature("Bold");
		break;
	case static_cast<int>(PokemonNature::Modest):
		_Pokemon->SetNature("Modest");
		break;
	case static_cast<int>(PokemonNature::Calm):
		_Pokemon->SetNature("Calm");
		break;
	case static_cast<int>(PokemonNature::Timid):
		_Pokemon->SetNature("Timid");
		break;
	case static_cast<int>(PokemonNature::Lonely):
		_Pokemon->SetNature("Lonely");
		break;
	case static_cast<int>(PokemonNature::Bashful):
		_Pokemon->SetNature("Bashful");
		break;
	case static_cast<int>(PokemonNature::Mild):
		_Pokemon->SetNature("Mild");
		break;
	case static_cast<int>(PokemonNature::Gentle):
		_Pokemon->SetNature("Gentle");
		break;
	case static_cast<int>(PokemonNature::Hasty):
		_Pokemon->SetNature("Hasty");
		break;
	case static_cast<int>(PokemonNature::Adamant):
		_Pokemon->SetNature("Adamant");
		break;
	case static_cast<int>(PokemonNature::Impish):
		_Pokemon->SetNature("Impish");
		break;
	case static_cast<int>(PokemonNature::Hardy):
		_Pokemon->SetNature("Hardy");
		break;
	case static_cast<int>(PokemonNature::Careful):
		_Pokemon->SetNature("Careful");
		break;
	case static_cast<int>(PokemonNature::Jolly):
		_Pokemon->SetNature("Jolly");
		break;
	case static_cast<int>(PokemonNature::Naughty):
		_Pokemon->SetNature("Naughty");
		break;
	case static_cast<int>(PokemonNature::Lax):
		_Pokemon->SetNature("Lax");
		break;
	case static_cast<int>(PokemonNature::Rash):
		_Pokemon->SetNature("Rash");
		break;
	case static_cast<int>(PokemonNature::Docile):
		_Pokemon->SetNature("Docile");
		break;
	case static_cast<int>(PokemonNature::Naive):
		_Pokemon->SetNature("Naive");
		break;
	case static_cast<int>(PokemonNature::Brave):
		_Pokemon->SetNature("Brave");
		break;
	case static_cast<int>(PokemonNature::Relaxed):
		_Pokemon->SetNature("Relaxed");
		break;
	case static_cast<int>(PokemonNature::Quiet):
		_Pokemon->SetNature("Quiet");
		break;
	case static_cast<int>(PokemonNature::Sassy):
		_Pokemon->SetNature("Sassy");
		break;
	case static_cast<int>(PokemonNature::Serious):
		_Pokemon->SetNature("Serious");
		break;
	}
}

PokemonSkillInfo* PokemonInfoManager::CreateSkillInfo(const std::string& _Key, int _Value, int _PP, PokemonType _Type, SkillType _SkillType, const std::string& _Desc)
{
	PokemonSkillInfo* NewSkill = new PokemonSkillInfo();
	std::string Key = GameEngineString::ToUpperReturn(_Key);

	NewSkill->SetName(Key);
	NewSkill->SetValue(_Value);
	NewSkill->SetPP(_PP);
	NewSkill->SetType(_Type);
	NewSkill->SetSkillType(_SkillType);
	NewSkill->SetDesc(_Desc);

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



