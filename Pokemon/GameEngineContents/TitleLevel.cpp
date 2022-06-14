#include "TitleLevel.h"
#include "TitleBackground.h"
#include <GameEngineContentsCore/GameEngineContentFont.h>
#include <string>
#include <GameEngineBase/GameEngineInput.h>
#include "Pokemon.h"
#include "PokemonEngine.h"

TitleLevel::TitleLevel() 
	: TitleIntro_(nullptr)
	, Fonts(nullptr)
	, BgmPlayer{}
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	GameEngineActor* Intro = CreateActor<TitleBackground>();
	
	TitleIntro_ = Intro->CreateRenderer("TitleImage_0.bmp");
}

void TitleLevel::Update()
{
	Time_ += GameEngineTime::GetDeltaTime();

	if (0.03f <= Time_ 
		&& 784 > Index_)
	{
		Time_ = 0.f;
		++Index_;

		TitleIntro_->SetImage("TitleImage_" + std::to_string(Index_) + ".bmp");
	}

	PokemonEngine* TmpEngine = dynamic_cast<PokemonEngine*>(&GameEngine::GetInst());

	if (nullptr != TmpEngine)
	{
		if (true == GameEngineInput::GetInst()->IsDown("TitleConfirm") || true == GameEngineInput::GetInst()->IsDown("Z"))
		{
			TmpEngine->ChangeLevel("WorldMap");
		}
	}
}

void TitleLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	BgmPlayer = GameEngineSound::SoundPlayControl("Title.mp3");
	BgmPlayer.SetVolume(0.5f);
}

void TitleLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	BgmPlayer.Stop();
}