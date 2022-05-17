#include "PokemonEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "TitleLevel.h"

PokemonEngine::PokemonEngine() 
{
}

PokemonEngine::~PokemonEngine() 
{
}

void PokemonEngine::GameInit() 
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 960, 640 });

	CreateLevel<TitleLevel>("Title");
	ChangeLevel("Title");
}

void PokemonEngine::GameLoop() 
{

}
void PokemonEngine::GameEnd() 
{

}