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
	, MyItem_(nullptr)
{
}

PokemonInfo::~PokemonInfo() 
{
	//std::vector<PokemonSkill*>::iterator StartIter = MySkills_.begin();
	//std::vector<PokemonSkill*>::iterator EndIter = MySkills_.end();

	//for (; StartIter != EndIter; StartIter++)
	//{
	//	if (nullptr != (*StartIter))
	//	{
	//		delete (*StartIter);
	//		(*StartIter) = nullptr;
	//	}
	//}
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

	MySkills_.push_back(_Skill);
}

void PokemonInfo::changeMySkill(int _Index, PokemonSkill* _Skill)
{
	if (4 <= _Index)
	{
		return;
	}

	MySkills_[_Index] = _Skill;
}


