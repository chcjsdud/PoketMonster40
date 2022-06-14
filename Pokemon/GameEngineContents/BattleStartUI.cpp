#include "BattleStartUI.h"
#include "ContentEnum.h"
#include "PlayerRed.h"
#include "WorldMapSoundManager.h"

BattleStartUI::BattleStartUI()
	: Renderer_(nullptr)
	, Type_(BattleNpcType::None)
	, AnimTimer_(0.0f)
	, Index_(0)
{
}

BattleStartUI::~BattleStartUI() 
{
}

void BattleStartUI::ChangeToBattleLevel(BattleNpcType _Type)
{
	Type_ = _Type;
}

void BattleStartUI::Start()
{
	NextLevelOn();
	SetPosition(PlayerRed::MainRed_->GetPosition());
	Renderer_ = CreateRenderer("BattleLoadImage_0.bmp", static_cast<int>(RenderOrder::UI));
	BgmPlayer_ = GameEngineSound::SoundPlayControl("Wild_Battle.mp3");
	BgmPlayer_.SetVolume(0.1f);
	WorldMapSoundManager::GetInst()->StopSound();

	PlayerRed::MainRed_->SetStartBattle(true);
}

void BattleStartUI::Update()
{
	SetPosition(PlayerRed::MainRed_->GetPosition());
	AnimTimer_ += GameEngineTime::GetDeltaTime();

	if (0.1f <= AnimTimer_)
	{
		AnimTimer_ = 0.f;
		Index_ += 1;

		if (Index_ > 9)
		{
			StartBattle();
			PlayerRed::MainRed_->SetStartBattle(false);
			Renderer_->Off();
			return;
		}

		Renderer_->SetImage("BattleLoadImage_" + std::to_string(Index_) + ".bmp");
	}
}

void BattleStartUI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void BattleStartUI::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	WorldMapLevel* CurrentLevel = dynamic_cast<WorldMapLevel*>(_NextLevel);
	if (nullptr != CurrentLevel)
	{
		BgmPlayer_.StopWithNullCheck();
		Death();
	}
}

void BattleStartUI::StartBattle()
{
	WorldMapLevel* CurrentLevel = dynamic_cast<WorldMapLevel*>(GetLevel());
	if (nullptr == CurrentLevel)
	{
		return;
	}

	switch (Type_)
	{
	case BattleNpcType::None:
		CurrentLevel->StartBattleLevelByWildeToWorld();
		break;
	case BattleNpcType::Brock:
		CurrentLevel->StartBattleLevelByNPC(BattleNpcType::Brock);
		break;
	case BattleNpcType::Rival:
		CurrentLevel->StartBattleLevelByNPC(BattleNpcType::Rival);
		break;
	default:
		break;
	}
}

