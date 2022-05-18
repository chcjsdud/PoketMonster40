#include "UITestLevel.h"
#include "PokemonMenu.h"
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
}

void UITestLevel::Update()
{
}
