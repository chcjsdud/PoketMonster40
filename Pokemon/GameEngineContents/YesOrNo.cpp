#include "YesOrNo.h"
#include "ContentEnum.h"
#include "InteractionText.h"
#include "PlayerRed.h"
#include "Green.h"
#include "RoomTileMap4.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>

YesOrNo::YesOrNo() 
	: UIRenderer_(nullptr)
	, ArrowRenderer_(nullptr)
	, Dialog_(nullptr)
	, Index_(0)
{
}

YesOrNo::~YesOrNo() 
{
}

void YesOrNo::Start()
{
	UIRenderer_ = CreateRenderer("ChoiceOption1.bmp", static_cast<int>(RenderOrder::UI));
	UIRenderer_->SetPivot({ 250, 30 });

	ArrowRenderer_ = CreateRenderer("ChoiceOption_Arrow.bmp", static_cast<int>(RenderOrder::UI));
	ArrowRenderer_->SetPivot({ 200, 0 });

	ArrowPos_.push_back({ 200, 0 });
	ArrowPos_.push_back({ 200, 60 });
}

void YesOrNo::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Z"))
	{
		SelectIndex();
	}
	if (true == GameEngineInput::GetInst()->IsDown("Up"))
	{
		Index_ -= 1;
	}
	if (true == GameEngineInput::GetInst()->IsDown("Down"))
	{
		Index_ += 1;
	}

	if (Index_ < 0)
	{
		Index_ = 0;
	}
	if (1 < Index_)
	{
		Index_ = 1;
	}

	ArrowRenderer_->SetPivot(ArrowPos_[Index_]);
}

void YesOrNo::SelectIndex()
{
	switch (Index_)
	{
	case 0:
	{
		PlayerRed::MainRed_->PopUpPokemonPreview(3);
		RoomTileMap4::GetInst()->Pokeball1->Off();
		Green::NPCGreen->SetSelectDialog(true);
		Dialog_->ClearText();
		Dialog_->AddText("This POKEMON is really quite");
		Dialog_->AddText("energetic!");
		Dialog_->AddText("Red received the SQUIRTLE");
		Dialog_->AddText("from PROF. OAK!");
		Dialog_->Setting();
		break;
	}
	break;
	case 1:
	{
		PlayerRed::MainRed_->PopUpPokemonPreview(3);
		break;
	}
	break;
	default:
		break;
	}
	Dialog_->ChoiceEnd();
	Death();
}


void YesOrNo::SetParent(InteractionText* _Parent)
{
	Dialog_ = _Parent;
}