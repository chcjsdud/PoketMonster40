#include "PokemonEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImageManager.h>
#include "TitleLevel.h"
#include "UITestLevel.h"


PokemonEngine::PokemonEngine() 
{
}

PokemonEngine::~PokemonEngine() 
{
}

void PokemonEngine::GameInit() 
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 960, 640 });

	InitUI();
	InitKey();

	CreateLevel<TitleLevel>("Title");
	CreateLevel<UITestLevel>("UITestLevel");
	ChangeLevel("Title");
}

void PokemonEngine::GameLoop() 
{
	if (GameEngineInput::GetInst()->IsDown("8") == true)
	{
		ChangeLevel("UITestLevel");
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
}
