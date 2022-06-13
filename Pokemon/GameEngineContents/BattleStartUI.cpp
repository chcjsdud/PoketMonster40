#include "BattleStartUI.h"

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
	Renderer_ = CreateRenderer("BattleLoadImage_0.bmp");
}

void BattleStartUI::Update()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();

	if (0.1f <= AnimTimer_)
	{
		AnimTimer_ = 0.f;
		Index_ += 1;
		if (Index_ > 9)
		{
			Index_ = 9;

		}

		Renderer_->SetImage("BattleLoadImage_" + std::to_string(Index_) + ".bmp");
	}
}

