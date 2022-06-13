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

	//////폰트 출력 테스트
	//{
	//	Fonts = CreateActor<GameEngineContentFont>();
	//	Fonts->SetPosition({ 200, 200 });
	//	Fonts->ShowString("Very Very \\ABCDEFGHIJ \\IntotheStage \\Red Is Red \\Blue Is Red! ", true);
	//	// \\ 시 문장 한 줄 뛰우기
	//}
}

void TitleLevel::Update()
{
	Time_ += GameEngineTime::GetDeltaTime();

	if (0.07f <= Time_ 
		&& 384 > Index_)
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

	//{
	//	// 폰트 출력이 완료되고 키입력 대기
	//	if (Fonts->IsWait())
	//	{
	//		// Z 키 입력시 다음 문장 출력
	//		if (GameEngineInput::GetInst()->IsDown("Z") == true)
	//		{
	//			// 다음 문장 출력 함수
	//			Fonts->NextString();
	//		}
	//	}
	//	// 다음 문장이 없을 때 == 끝났을 때
	//	if (Fonts->IsEnd())
	//	{
	//		// 모든 대화가 끝났을 때 z 키누르면 다음 대화 시작
	//		if (GameEngineInput::GetInst()->IsDown("Z") == true)
	//		{
	//			// 출력된 함수 삭제
	//			Fonts->ShowString("String Is Hard\\ABCDEFGHIJ \\VeryHard \\Red Is Red? \\Blue Is Red! ");
	//		}
	//		// 모든 대화가 끝났을 때 x 키누르면 종료
	//		else if (GameEngineInput::GetInst()->IsDown("X") == true)
	//		{
	//			Fonts->EndFont();
	//		}
	//	}
	//}

}

void TitleLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	BgmPlayer = GameEngineSound::SoundPlayControl("Title(recorder).mp3");
	BgmPlayer.SetVolume(0.5f);
}
void TitleLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	BgmPlayer.Stop();
}