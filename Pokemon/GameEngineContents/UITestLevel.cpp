#include "UITestLevel.h"
#include "PokemonMenu.h"
#include "PokemonSummaryMenu.h"
#include <GameEngineBase/GameEngineInput.h>

UITestLevel::UITestLevel()
{
}

UITestLevel::~UITestLevel()
{
}



void UITestLevel::Loading()
{
	PokemonMenu_ = CreateActor<PokemonMenu>(0, "PokemonMenu");
	//CreateActor<PokemonSummaryMenu>(0, "PokemonSummaryMenu");
}

void UITestLevel::Update()
{
}
