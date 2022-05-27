#include "PokemonSkillInfo.h"

PokemonSkillInfo::PokemonSkillInfo() 
	: Value_(0)
	, PP_(0)
	, SkillType_(SkillType::Physical)
	, Type_(PokemonType::NORMAL)
	, Effect_{}
	, Desc_{}
{
}

PokemonSkillInfo::~PokemonSkillInfo() 
{
}



