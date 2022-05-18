#include "Pokemon.h"
#include <GameEngine/GameEngineImageManager.h>

Pokemon::Pokemon() 
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
	, IsPlayer_(false)
	, IsGender_(false)
	, BattleBack_()
	, BattleFront_()
	, MyProfile_()
	, MyIcon_()
	, MySkills_{nullptr}
{

}

Pokemon::~Pokemon() 
{
}

void Pokemon::Start()
{
	MySkills_.reserve(4);
}

void Pokemon::Update()
{
}



void Pokemon::SetPokemonImage(const std::string _Name)
{
	BattleBack_ = _Name + "B.bmp";
	BattleFront_ = _Name + "F.bmp";//전투 앞모습(적 혹은 야생 포켓몬
	MyIcon_ = _Name + "_mini.bmp"; //지닌 포켓몬 아이콘

	//MyIcon_ Cut
	GameEngineImage* MyIconImage = GameEngineImageManager::GetInst()->Find(MyIcon_);
	MyIconImage->Cut({ MyIconImage->GetScale().Half().x,MyIconImage->GetScale().y });
}