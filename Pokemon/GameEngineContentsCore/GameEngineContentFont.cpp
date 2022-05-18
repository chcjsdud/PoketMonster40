#include "GameEngineContentFont.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineContentFont::GameEngineContentFont() 
	: CurrentPivot_(float4::ZERO)
	, OriginalWaitTime_(0)
	, CurrentWaitTime_(0)
	, CurrentStringRow_(0)
	, WatingKeyPush_(false)
{
}

GameEngineContentFont::~GameEngineContentFont() 
{

}

void GameEngineContentFont::Start()
{
	//std::list<GameEngineContentFont*> GameEngineContentFont::AllFonts_.push_back(this);
	Off();
}

void GameEngineContentFont::Update()
{
	if (StringQueue_.empty() == false && WatingKeyPush_ == false)
	{
		CurrentWaitTime_ -= GameEngineTime::GetDeltaTime(3);
		if (CurrentWaitTime_ < 0)
		{
			std::string StringForRendererName = "";
			char CurrentWord = CurrentString_[0];

			if (65 <= CurrentWord && CurrentWord <= 90)
			{
				StringForRendererName = CurrentWord;
				StringForRendererName += "_Upper.bmp";
			}
			else if (97 <= CurrentWord && CurrentWord <= 122)
			{
				StringForRendererName = CurrentWord;
				StringForRendererName += "_Lower.bmp";
			}

			CurrentString_.erase(0, 1);
			GameEngineRenderer* CurrentRenderer = CreateRenderer(StringForRendererName, 10, RenderPivot::LeftTop, CurrentPivot_);
			CurrentPivot_ = { CurrentPivot_.x + CurrentRenderer->GetImageScale().x , static_cast<float>(60 * CurrentStringRow_)};
			CurrentWaitTime_ = OriginalWaitTime_;
		}

		// 아래는 예외처리

		// 줄 바꿈
		if (CurrentString_.empty() == true || CurrentString_.front() == '\\')
		{
			if (CurrentStringRow_ > 1)
			{
				// 입력 대기
				WatingKeyPush_ = true;
			}
			++CurrentStringRow_;
			CurrentPivot_ = { 10, static_cast<float>(60 * CurrentStringRow_)};
			StringQueue_.pop();
			// 입력된 대화 모두 출력완료
			if (StringQueue_.empty())
			{
				WatingKeyPush_ = true;
			}
			else
			{
				CurrentString_ = StringQueue_.front();
			}
		}
	}
}

bool GameEngineContentFont::ShowString(const std::string& _String, float _WaitTime /* = 0.02f*/)
{
	if (GetPosition().CompareInt2D(float4::ZERO))
	{
		MsgBoxAssert("폰트 출력할 위치가 설정이 안되어 있습니다");
		return false;
	}

	if (StringQueue_.empty() == false)
	{
		return false;
	}


	CurrentString_.clear();
	CurrentStringRow_ = 0;
	OriginalWaitTime_ = _WaitTime;
	CurrentWaitTime_ = 0;
	std::string GetString = _String;
	int IdxCount= 0;

	// 위치에서부터 10픽셀 옆에서 최초 문자 생성
	CurrentPivot_ = { 10, 0 };

	WatingKeyPush_ = false;


	while (GetString.empty() == false)
	{
		if (GetString[IdxCount] == 0)
		{
			StringQueue_.push(GetString.substr(0, IdxCount));
			break;
		}
		if (GetString[IdxCount] == '\\')
		{
			++IdxCount;
			StringQueue_.push(GetString.substr(0, IdxCount));
			GetString.erase(0, IdxCount);
			IdxCount = 0;
		}
		else
		{
			++IdxCount;
		}
	}
	CurrentString_ = StringQueue_.front();
	On();
	return true;
}


//void GameEngineContentFont::Destroy()
//{
//	//for (auto Font : AllFonts_)
//	//{
//	//	if (Font != nullptr)
//	//	{
//	//		delete Font;
//	//		Font = nullptr;
//	//	}
//	//}
//}