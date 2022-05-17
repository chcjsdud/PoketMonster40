#include "PokemonEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImageManager.h>
#include "TitleLevel.h"
#include "UITestLevel.h"
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

	InitUI();
	InitKey();

	CreateLevel<TitleLevel>("Title");
	CreateLevel<UITestLevel>("UITestLevel");
	CreateLevel<WorldMapLevel>("WorldMap");
	ChangeLevel("Title");
}

void PokemonEngine::GameLoop() 
{
	if (GameEngineInput::GetInst()->IsDown("8") == true)
	{
		ChangeLevel("UITestLevel");
	}

	if (GameEngineInput::GetInst()->IsDown("WoldMapTest") == true)
	{
		ChangeLevel("WorldMap");
	}
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

void PokemonEngine::InitKey()
{
	GameEngineInput::GetInst()->CreateKey("Up", 0x26);
	GameEngineInput::GetInst()->CreateKey("Down", 0x28);
	GameEngineInput::GetInst()->CreateKey("Left", 0x25);
	GameEngineInput::GetInst()->CreateKey("Right", 0x27);

	GameEngineInput::GetInst()->CreateKey("Z", 'Z');
	GameEngineInput::GetInst()->CreateKey("X", 'X');

	GameEngineInput::GetInst()->CreateKey("8", 0x38); //UI테스트레벨로 텔포용 키

	GameEngineInput::GetInst()->CreateKey("WoldMapTest", VK_NUMPAD0); //월드맵 레벨로 텔포용 키
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