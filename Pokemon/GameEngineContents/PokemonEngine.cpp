#include "PokemonEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImageManager.h>
#include "PokemonInfoManager.h"
#include "TitleLevel.h"
#include "UITestLevel.h"
#include "BagTestLevel.h"
#include "WorldMapLevel.h"
#include "BattleLevel.h"
#include "MonsterBall.h"
#include "Potion.h"
#include <GameEngineBase/GameEngineRandom.h>

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
	InitFont();

	PokemonInfoManager::GetInst().Reset();

	CreateLevel<TitleLevel>("Title");
	CreateLevel<UITestLevel>("UITestLevel");
	CreateLevel<BagTestLevel>("BagTestLevel");
	CreateLevel<WorldMapLevel>("WorldMap");
	CreateLevel<BattleLevel>("Battle");
	ChangeLevel("Title");

}

void PokemonEngine::GameLoop()
{
	if (GameEngineInput::GetInst()->IsDown("8") == true)
	{
		ChangeLevel("UITestLevel");
	}

	//if (GameEngineInput::GetInst()->IsDown("Bag") == true)
	//{
	//	ChangeLevel("BagTestLevel");
	//}

	if (GameEngineInput::GetInst()->IsDown("WoldMapTest") == true)
	{
		ChangeLevel("WorldMap");
	}


	if (GameEngineInput::GetInst()->IsDown("Battle") == true)
	{
		ChangeLevel("Battle");
	}

	// 충돌체 체크용
	if (GameEngineInput::GetInst()->IsDown("test") == true)
	{
		GameEngineLevel::IsDebugModeSwitch();
	}
}

void PokemonEngine::GameEnd() 
{
	PokemonInfoManager::Destroy();
	GameEngineRandom::Destroy();
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
	GameEngineInput::GetInst()->CreateKey("Bag", VK_LSHIFT); //UI테스트레벨로 텔포용 키

	GameEngineInput::GetInst()->CreateKey("WoldMapTest", VK_NUMPAD0); //월드맵 레벨로 텔포용 키

	GameEngineInput::GetInst()->CreateKey("Battle", VK_RETURN);
	
	GameEngineInput::GetInst()->CreateKey("test", 'M'); // 충돌체 체크용 키
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

	{
		GameEngineDirectory ResourcesDirectory;
		ResourcesDirectory.MoveParent("Pokemon");
		ResourcesDirectory.Move("Resources");
		ResourcesDirectory.Move("KYN-AllResources");
		ResourcesDirectory.Move("Battle_X4");//경로에 같은 이름 이미지 파일있으면 터지네용
		std::vector<GameEngineFile> AllFileVec = ResourcesDirectory.GetAllFile();
		for (int i = 0; i < AllFileVec.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllFileVec[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory ResourcesDirectory;
		ResourcesDirectory.MoveParent("Pokemon");
		ResourcesDirectory.Move("Resources");
		ResourcesDirectory.Move("KYN-AllResources");
		ResourcesDirectory.Move("Effect");
		std::vector<GameEngineFile> AllFileVec = ResourcesDirectory.GetAllFile();
		for (int i = 0; i < AllFileVec.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllFileVec[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory ResourcesDirectory;
		ResourcesDirectory.MoveParent("Pokemon");
		ResourcesDirectory.Move("Resources");
		ResourcesDirectory.Move("NPC");
		ResourcesDirectory.Move("4");
		std::vector<GameEngineFile> AllFileVec = ResourcesDirectory.GetAllFile();
		for (int i = 0; i < AllFileVec.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllFileVec[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory ResourcesDirectory;
		ResourcesDirectory.MoveParent("Pokemon");
		ResourcesDirectory.Move("Resources");
		ResourcesDirectory.Move("NPC");
		ResourcesDirectory.Move("7");
		std::vector<GameEngineFile> AllFileVec = ResourcesDirectory.GetAllFile();
		for (int i = 0; i < AllFileVec.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllFileVec[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory ResourcesDirectory;
		ResourcesDirectory.MoveParent("Pokemon");
		ResourcesDirectory.Move("Resources");
		ResourcesDirectory.Move("UI");
		ResourcesDirectory.Move("ChoiceOption");
		std::vector<GameEngineFile> AllFileVec = ResourcesDirectory.GetAllFile();
		for (int i = 0; i < AllFileVec.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllFileVec[i].GetFullPath());
		}
	}
}

void PokemonEngine::ImageCut()
{
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("Flower.bmp");
		Image->CutCount(5, 1);
	}
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("BushEffect.bmp");
		Image->CutCount(4, 1);
	}
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("None.bmp");
		Image->CutCount(1, 1);
	}
}

void PokemonEngine::InitFont()
{
	{
		GameEngineDirectory ResourecesDir;
		ResourecesDir.MoveParent("Pokemon");
		ResourecesDir.Move("Resources");
		ResourecesDir.Move("UI");
		ResourecesDir.Move("Fonts");
		ResourecesDir.Move("Index");
		ResourecesDir.Move("Upper");


		std::vector<GameEngineFile> AllImageFileList = ResourecesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		};
	}

	{
		GameEngineDirectory ResourecesDir;
		ResourecesDir.MoveParent("Pokemon");
		ResourecesDir.Move("Resources");
		ResourecesDir.Move("UI");
		ResourecesDir.Move("Fonts");
		ResourecesDir.Move("Index");
		ResourecesDir.Move("Number");


		std::vector<GameEngineFile> AllImageFileList = ResourecesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		};
	}
	{
		GameEngineDirectory ResourecesDir;
		ResourecesDir.MoveParent("Pokemon");
		ResourecesDir.Move("Resources");
		ResourecesDir.Move("UI");
		ResourecesDir.Move("Fonts");
		ResourecesDir.Move("Index");
		ResourecesDir.Move("Lower");


		std::vector<GameEngineFile> AllImageFileList = ResourecesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		};
	}
	{
		GameEngineDirectory ResourecesDir;
		ResourecesDir.MoveParent("Pokemon");
		ResourecesDir.Move("Resources");
		ResourecesDir.Move("UI");
		ResourecesDir.Move("Fonts");
		ResourecesDir.Move("Index");
		ResourecesDir.Move("Other");


		std::vector<GameEngineFile> AllImageFileList = ResourecesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		};
	}
}