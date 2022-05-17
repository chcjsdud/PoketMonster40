#include "UITestLevel.h"
#include "PokemonMenu.h"

UITestLevel::UITestLevel()
{
}

UITestLevel::~UITestLevel()
{
}



void UITestLevel::Loading()
{
	CreateActor<PokemonMenu>(0, "PokemonMenu");
}

void UITestLevel::Update()
{
}
