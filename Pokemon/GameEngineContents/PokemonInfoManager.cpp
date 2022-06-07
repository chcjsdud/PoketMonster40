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
int PokemonInfoManager::PokemonId_ = 0;

PokemonInfoManager::PokemonInfoManager() 
{

}

PokemonInfoManager::~PokemonInfoManager()
{
	//게임의 모든 포켓몬 및 포켓몬, 스킬, 아이템 정보 삭제
	{
		std::map<int, Pokemon*>::iterator StartIter = AllPokemonList_.begin();
		std::map<int, Pokemon*>::iterator EndIter = AllPokemonList_.end();

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


	//게임의 모든 스킬 및 아이템 삭제
	{
		std::vector<PokemonSkill*>::iterator StartIter = AllPokemonSkillList_.begin();
		std::vector<PokemonSkill*>::iterator EndIter = AllPokemonSkillList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr != (*StartIter))
			{
				delete (*StartIter);
				(*StartIter) = nullptr;
			}
		}
	}

	{
		std::vector<Item*>::iterator StartIter = AllItemList_.begin();
		std::vector<Item*>::iterator EndIter = AllItemList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr != (*StartIter))
			{
				delete (*StartIter);
				(*StartIter) = nullptr;
			}
		}
	}
}


void PokemonInfoManager::Reset()
{
	{
		//Tackle: 몸통박치기
		PokemonSkillInfo* Tackle = CreateSkillInfo("Tackle", 40, 35, PokemonType::NORMAL, SkillType::Physical, "A physical attack in which the user charges,\\full body, into the foe.");
		//Tail Whip: 꼬리 흔들기 
		PokemonSkillInfo* TailWhip = CreateSkillInfo("TailWhip", 10, 30, PokemonType::NORMAL, SkillType::Status, "Lowers the opponent's Pokémon's Defense by 1 stage.");
		//Scratch: 할퀴기
		PokemonSkillInfo* Scratch = CreateSkillInfo("Scratch", 40, 35, PokemonType::NORMAL, SkillType::Physical, "Hard, pointed, and sharp claws rake the foe.");
		//Scratch: 울음소리 
		PokemonSkillInfo* Growl = CreateSkillInfo("Growl", 10, 40, PokemonType::NORMAL, SkillType::Status, "The user growls in a cute way, making the foe lower its Attack. stat.");

		//Withdraw: 껍질에 숨기
		PokemonSkillInfo* Withdraw = CreateSkillInfo("Withdraw", 10, 20, PokemonType::WATER, SkillType::Status, "The user withdraws its body in its hard shell, raising its Defense stat.");
		//WaterGun: 물대포
		PokemonSkillInfo* WaterGun = CreateSkillInfo("WaterGun", 10, 20, PokemonType::WATER, SkillType::Special, "The foe is struck with a lot of water expelled forcibly through the mouth.");

		//RockTomb: 암석봉인
		PokemonSkillInfo* RockTomb = CreateSkillInfo("RockTomb", 10, 20, PokemonType::ROCK, SkillType::Physical, "Boulders are hurled at the foe. It also lowers the foe's Speed if it hits.");
	}

	{
		//Charmander: 파이리
		PokemonInfo* CharmanderInfo = CreatePokemonInfo("Charmander", PokemonType::FIRE, 5, 10, 10, 12, 10, 12, 19);
		//스킬 초기화
		CharmanderInfo->AddMySkill(CreatePokemonSkill("Scratch"));
		CharmanderInfo->AddMySkill(CreatePokemonSkill("Growl"));

		//Squirtle: 꼬부기
		PokemonInfo* SquirtleInfo = CreatePokemonInfo("Squirtle", PokemonType::WATER, 5, 12, 11, 10, 10, 9, 19);
		SquirtleInfo->AddMySkill(CreatePokemonSkill("Tackle"));
		SquirtleInfo->AddMySkill(CreatePokemonSkill("TailWhip"));

		//Bulbasaur: 이상해씨
		PokemonInfo* BulbasaurInfo = CreatePokemonInfo("Bulbasaur", PokemonType::GRASS, 5, 11, 11, 12, 12, 9, 19);
		BulbasaurInfo->AddMySkill(CreatePokemonSkill("Tackle"));
		BulbasaurInfo->AddMySkill(CreatePokemonSkill("Growl"));

		//Pidgey: 구구
		PokemonInfo* PidgeyInfo = CreatePokemonInfo("Pidgey", PokemonType::FLYING, 1, 45, 40, 35, 35, 56, 40);
		PidgeyInfo->AddMySkill(CreatePokemonSkill("Tackle"));

		//Rattata: 꼬렛
		PokemonInfo* RattataInfo = CreatePokemonInfo("Rattata", PokemonType::NORMAL, 1, 56, 35, 25, 35, 72, 30);
		RattataInfo->AddMySkill(CreatePokemonSkill("Tackle"));
		RattataInfo->AddMySkill(CreatePokemonSkill("TailWhip"));

		//Geodude: 꼬마돌
		PokemonInfo* Geodude = CreatePokemonInfo("Geodude", PokemonType::ROCK, 12, 10, 10, 15, 15, 5);
		Geodude->AddMySkill(CreatePokemonSkill("Tackle"));

		//Onix: 롱스톤
		PokemonInfo* Onix = CreatePokemonInfo("Onix", PokemonType::ROCK, 14, 10, 10, 15, 15, 5);
		Onix->AddMySkill(CreatePokemonSkill("Tackle"));
		Onix->AddMySkill(CreatePokemonSkill("Growl"));
		Onix->AddMySkill(CreatePokemonSkill("RockTomb"));
	}

	{
		ItemInfo* MonsterBall = CreateItemInfo("Pokeball", 10, ItemType::BALL, "A Ball thrown to catch a Pokemon.\\It is designed in a capsule style.");
		ItemInfo* Potion = CreateItemInfo("Potion", 10, ItemType::ITEM, "A Potion is an item that\\heals 20 HP of a Pokemon.");
	}


	//디버깅 포켓몬
	Pokemon* pokemon = CreatePokemon("Rattata");
}




//////////////////////////////////////////////////객체//////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

//정보를 바탕으로 한 객체 생성 함수
//정보와 객체를 따로 둔 이유: 정보를 객체에게 전달해주어 객체를 메모리 주소와 관계없이 여러 개 생성할 수 있도록 함
Pokemon* PokemonInfoManager::CreatePokemon(const std::string& _Name)
{
	Pokemon* NewPokemon = new Pokemon();
	PokemonInfo* MyInfo = FindPokemonInfo(_Name);

	//정보를 복사
	NewPokemon->GetInfo()->SetName(_Name);
	NewPokemon->GetInfo()->SetMyId(10000 + PokemonId_);
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
	NewPokemon->GetInfo()->SetPokemonImage(_Name); 

	for (int i = 0; i < MyInfo->GetSkill().size(); ++i)
	{
		std::vector<PokemonSkill*> SkillList = MyInfo->GetSkill();

		PokemonSkill* NewnSkill = CreatePokemonSkill(SkillList[i]->GetInfo()->GetNameCopy());
		NewPokemon->GetInfo()->AddMySkill(NewnSkill);
	}

	CreateRandomNature(NewPokemon->GetInfo());

	++PokemonId_;

	AllPokemonList_.insert(std::make_pair(NewPokemon->GetInfo()->GetMyId(), NewPokemon));

	return NewPokemon;
}

void PokemonInfoManager::DestroyPokemon(int _Id)
{
	std::map<int, Pokemon*>::iterator StartIter = AllPokemonList_.begin();
	std::map<int, Pokemon*>::iterator EndIter = AllPokemonList_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			if (_Id == (*StartIter->second).GetInfo()->GetMyId())
			{
				delete StartIter->second;
				StartIter->second = nullptr;
			}
		}
	}
}

Pokemon* PokemonInfoManager::FindPokemon(int _Id)
{
	std::map<int, Pokemon*>::iterator StartIter = AllPokemonList_.begin();
	std::map<int, Pokemon*>::iterator EndIter = AllPokemonList_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			if (_Id == (*StartIter->second).GetInfo()->GetMyId())
			{
				return StartIter->second;
			}
		}
	}

	return nullptr;
}

PokemonSkill* PokemonInfoManager::CreatePokemonSkill(const std::string& _Name)
{
	PokemonSkill* NewPokemonSkill = new PokemonSkill();
	PokemonSkillInfo* MyInfo = FindSkillInfo(_Name);

	NewPokemonSkill->GetInfo()->SetName(MyInfo->GetNameCopy());
	NewPokemonSkill->GetInfo()->SetType(MyInfo->GetType());
	NewPokemonSkill->GetInfo()->SetSkillType(MyInfo->GetSkillType());
	NewPokemonSkill->GetInfo()->SetValue(MyInfo->GetValue());
	NewPokemonSkill->GetInfo()->SetDesc(MyInfo->GetDesc());
	NewPokemonSkill->GetInfo()->SetPP(MyInfo->GetPP());
	NewPokemonSkill->GetInfo()->SetEffect(MyInfo->GetEffect());

	AllPokemonSkillList_.push_back(NewPokemonSkill);
	return NewPokemonSkill;
}

Item* PokemonInfoManager::CreateItem(const std::string& _Name)
{
	Item* NewItem = new Item();	
	ItemInfo* MyInfo = FindItemInfo(_Name);

	NewItem->GetInfo()->SetName(MyInfo->GetNameCopy());
	NewItem->GetInfo()->SetType(MyInfo->GetType());
	NewItem->GetInfo()->SetValue(MyInfo->GetValue());
	NewItem->GetInfo()->SetDesc(MyInfo->GetDesc());

	AllItemList_.push_back(NewItem);
	return NewItem;
}









//////////////////////////////////////////////////정보//////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

//정보 생성 함수
//포인터 선언 이유: 값형으로 바꿔보았으나 전투 쪽 복사 생성자 오류 및 관리 난이도 상승
PokemonInfo* PokemonInfoManager::CreatePokemonInfo(const std::string& _Key, PokemonType _Type, int _Lv, int _Att, int _Def, int _SpAtt, int _SpDef, int _Speed, int _HP)
{
	PokemonInfo* NewPokemonInfo = new PokemonInfo();

	NewPokemonInfo->SetName(_Key);
	NewPokemonInfo->SetMyId(0);
	NewPokemonInfo->SetMyType(_Type);
	NewPokemonInfo->SetStatusEffect(StatusEffect::NONE);
	NewPokemonInfo->SetMyLevel(_Lv);
	NewPokemonInfo->SetMyMaxLevel(100);
	NewPokemonInfo->SetHp(_HP);
	NewPokemonInfo->SetMaxHp(_HP);
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

ItemInfo* PokemonInfoManager::CreateItemInfo(const std::string& _Key, int _Value, ItemType _Type, const std::string& _Desc)
{
	ItemInfo* NewItem = new ItemInfo();
	std::string Key = GameEngineString::ToUpperReturn(_Key);

	NewItem->SetName(Key);
	NewItem->SetValue(_Value);
	NewItem->SetDesc(_Desc);
	NewItem->SetType(_Type);

	AllItemInfoList_.insert(std::make_pair(Key, NewItem));
	return NewItem;
}



//정보 찾는 함수
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