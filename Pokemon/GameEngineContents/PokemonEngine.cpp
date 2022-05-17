#include "PokemonEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include "TitleLevel.h"


PokemonEngine::PokemonEngine() 
{
}

PokemonEngine::~PokemonEngine() 
{
}

void PokemonEngine::GameInit() 
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	InitUI();

	CreateLevel<TitleLevel>("Title");
	ChangeLevel("Title");
}

void PokemonEngine::GameLoop() 
{

}
void PokemonEngine::GameEnd() 
{

}

void PokemonEngine::InitUI()
{
	{
		GameEngineDirectory ResourecesDir;
		ResourecesDir.MoveParent("Pokemon");
		ResourecesDir.Move("Resources");
		ResourecesDir.Move("UI");
		ResourecesDir.Move("X4");

		std::vector<GameEngineFile> AllImageFileList = ResourecesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		};
	}
}
