#include "GameEngineContentFont.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineContentFont::GameEngineContentFont() 
	: WaitTime_(0.02f)
	, FirstCharPos_(float4::ZERO)
	, CurrentWord_(0)
{
}

GameEngineContentFont::~GameEngineContentFont() 
{

}

void GameEngineContentFont::Start()
{
	GameEngineContentFont::AllFonts_.push_back(this);
	Off();
}

void GameEngineContentFont::Update()
{
	if (StringQueue_.empty() == false)
	{
		WaitTime_ -= GameEngineTime::GetDeltaTime(3);
		if (WaitTime_ < 0)
		{

		}
	}
	
}

bool GameEngineContentFont::ShowString(const std::string& _String, float _WaitTime /* = 0.01f*/)
{
	if (FirstCharPos_.CompareInt2D(float4::ZERO))
	{
		MsgBoxAssert("폰트 출력할 위치가 설정이 안되어 있습니다");
		return false;
	}

	if (StringQueue_.empty() == false)
	{
		return false;
	}

	WaitTime_ = _WaitTime * 2.0f;
	StringQueue_ = _String;
	CurrentWord_ = StringQueue_[0];
	On;
}


void GameEngineContentFont::Destroy()
{
	for (auto Font : AllFonts_)
	{
		if (Font != nullptr)
		{
			delete Font;
			Font = nullptr;
		}
	}
}