#include "TitleLevel.h"
#include "TitleBackground.h"
#include <GameEngineContentsCore/GameEngineContentFont.h>
#include <string>
#include <GameEngineBase/GameEngineInput.h>

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackground>();


	////폰트 출력 테스트
	{
		Fonts = CreateActor<GameEngineContentFont>();
		Fonts->SetPosition({ 200, 200 });
		// \\ 시 문장 한 줄 뛰우기
		Fonts->ShowString("Very Very \\ ABCDEFGHIJ \\ IntotheStage \\ Red Is Red \\ Blue Is Red! ");
	}
}

void TitleLevel::Update()
{

	{
		// 폰트 출력이 완료되고 키입력 대기
		if (Fonts->IsWait())
		{
			// Z 키 입력시 다음 문장 출력
			if (GameEngineInput::GetInst()->IsDown("Z") == true)
			{
				// 다음 문장 출력 함수
				Fonts->NextString();
			}
			// 다음 문장이 없을 때 == 끝났을 때
			if (Fonts->IsEnd())
			{
				int a = 0;
			}
		}
	}

}