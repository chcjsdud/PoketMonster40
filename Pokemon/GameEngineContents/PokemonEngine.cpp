#include "PokemonEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineInput.h>

#include "TitleLevel.h"
#include "WorldMapLevel.h"

PokemonEngine::PokemonEngine() 
{
}

PokemonEngine::~PokemonEngine() 
{
}

void PokemonEngine::GameInit() 
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 960, 640 });
	ResourcesLoad();
	ImageCut();

	CreateLevel<TitleLevel>("Title");
	CreateLevel<WorldMapLevel>("WorldMap");
	ChangeLevel("Title");

	if (false == GameEngineInput::GetInst()->IsKey("Exit"))
	{
		GameEngineInput::GetInst()->CreateKey("Exit", VK_ESCAPE);
		GameEngineInput::GetInst()->CreateKey("ChangeLevelTitle", 'Z');
		GameEngineInput::GetInst()->CreateKey("ChangeLevelWorld", 'X');
	}
}

void PokemonEngine::GameLoop() 
{
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelTitle"))
	{
		ChangeLevel("Title");
	}
	if (true == GameEngineInput::GetInst()->IsDown("ChangeLevelWorld"))
	{
		ChangeLevel("WorldMap");
	}
}
void PokemonEngine::GameEnd() 
{

}

void PokemonEngine::ResourcesLoad()
{
	{
		GameEngineDirectory ResourcesDirectory;
		ResourcesDirectory.MoveParent("Pokemon");
		ResourcesDirectory.Move("Resources");
		ResourcesDirectory.Move("WorldMapBackground");
		std::vector<GameEngineFile> AllFileVec = ResourcesDirectory.GetAllFile();
		for (int i = 0; i < AllFileVec.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllFileVec[i].GetFullPath());
		}
	}
}

void PokemonEngine::ImageCut()
{
}
