#include "PokemonInfo.h"
#include <GameEngine/GameEngineImageManager.h>

PokemonInfo::PokemonInfo() 
	: Type_(PokemonType::NORMAL)
	, Effect_(StatusEffect::NONE)
	, Lv_(1)
	, MaxLv_(100)
	, Hp_(100)
	, MaxHp_(100)
	, Exp_(0)
	, MaxExp_(100)
	, Att_(0)
	, Def_(0)
	, SpAtt_(0)
	, SpDef_(0)
	, Speed_(0)
	, IsFaint_(false)
	, IsPlayer_(false)
	, IsGender_(false)
	, BattleBack_()
	, BattleFront_()
	, MyProfile_()
	, MyIcon_()
	, MySkills_{}
	, MySkillCount_(0)
	, MyItem_(nullptr)
{
	MySkills_.resize(4);
	MySkillCount_ = 0;
}

PokemonInfo::~PokemonInfo() 
{
}

void PokemonInfo::SetPokemonImage(const std::string _Name)
{
	BattleBack_ = _Name + "B.bmp";
	BattleFront_ = _Name + "F.bmp";//전투 앞모습(적 혹은 야생 포켓몬
	MyIcon_ = _Name + "_mini.bmp"; //지닌 포켓몬 아이콘

	//MyIcon_ Cut
	GameEngineImage* MyIconImage = GameEngineImageManager::GetInst()->Find(MyIcon_);
	MyIconImage->Cut({ MyIconImage->GetScale().Half().x,MyIconImage->GetScale().y });
}

void PokemonInfo::AddMySkill(PokemonSkillInfo* _Skill)
{
	if (4 <= MySkillCount_)
	{
		return;
	}

	switch (MySkillCount_)
	{
	case 0:
		if (nullptr == MySkills_[0])
		{
			MySkills_[0] = _Skill;
		}
		break;

	case 1:
		if (nullptr == MySkills_[1])
		{
			MySkills_[1] = _Skill;
		}
		break;

	case 2:
		if (nullptr == MySkills_[2])
		{
			MySkills_[2] = _Skill;
		}
		break;

	case 3:
		if (nullptr == MySkills_[3])
		{
			MySkills_[3] = _Skill;
		}
		break;
	}

	++MySkillCount_;
}
