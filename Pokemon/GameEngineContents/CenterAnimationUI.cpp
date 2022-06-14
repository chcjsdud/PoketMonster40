#include "CenterAnimationUI.h"
#include "ContentEnum.h"

CenterAnimationUI::CenterAnimationUI() 
	: LeftRenderer_(nullptr)
	, UpRenderer_(nullptr)
{
}

CenterAnimationUI::~CenterAnimationUI() 
{
}

void CenterAnimationUI::MakeBalls(int _Count)
{
	for (int i = 0; i < _Count; i++)
	{
		LeftBallRenderers_.push_back(CreateRenderer("PokemonCenter_Anim.bmp"));
	}
}

void CenterAnimationUI::Start()
{
	LeftRenderer_ = CreateRenderer("PokemonCenter_Anim.bmp");
	UpRenderer_ = CreateRenderer("PokemonCenter_Anim.bmp");
}

void CenterAnimationUI::Update()
{
}

