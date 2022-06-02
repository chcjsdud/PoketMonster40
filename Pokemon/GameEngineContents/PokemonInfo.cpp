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
	, PokemonNature_()
	, BattleBack_()
	, BattleFront_()
	, MyProfile_()
	, MyIcon_()
	, MySkills_{}
	, MySkillCount_(0)
	, MyItem_(nullptr)
{
}

PokemonInfo::~PokemonInfo() 
{
	//자신이 가지고 있는 스킬을 삭제(이 스킬은 인포매니저에서 삭제해주지 않는다)
	std::vector<PokemonSkill*>::iterator StartIter = MySkills_.begin();
	std::vector<PokemonSkill*>::iterator EndIter = MySkills_.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if (nullptr != (*StartIter))
		{
			delete (*StartIter);
			(*StartIter) = nullptr;
		}
	}
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

void PokemonInfo::AddMySkill(PokemonSkill* _Skill)
{
	if (4 <= MySkills_.size())
	{
		return;
	}

	switch (MySkills_.size() - 1)
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
