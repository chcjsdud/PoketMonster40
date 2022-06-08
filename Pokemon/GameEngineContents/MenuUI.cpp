#include "MenuUI.h"

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>

#include <GameEngine/GameEngineRenderer.h>

#include "PlayerRed.h"
#include "FadeActor.h"
#include "PokemonMenu.h"
#include "Bag.h"

MenuUI::MenuUI():
	CurrentOrder_(0),
	IsOn_(false),
	FadeActor_(nullptr),
	MenuUITimer_(0.0f)
{
	MenuUIRenderer_.reserve(6);
}

MenuUI::~MenuUI()
{
}

void MenuUI::InitMenuUI()
{
	//FadeActor 생성
	FadeActor_ = GetLevel()->CreateActor<FadeActor>();
	FadeActor_->SetPosition(GetPosition() + GameEngineWindow::GetScale().Half());

	MenuUIRenderer_[0]->On();
	IsOn_ = true;
}

void MenuUI::Start()
{
	//렌더러 초기화
	for (size_t i = 0; i < 6; i++)
	{
		GameEngineRenderer* NewRenderer = CreateRenderer(GetOrder(), RenderPivot::LeftTop);
		NewRenderer->SetImage("MenuUI_" + std::to_string(i) + ".bmp");
		NewRenderer->SetTransColor(RGB(255, 0, 255));
		NewRenderer->Off();
		MenuUIRenderer_.push_back(NewRenderer);
	}
}

void MenuUI::Update()
{
	if (IsOn_ == false)
	{
		return;
	}
	if (ChildUI_ != nullptr)
	{
		if (ChildUI_->IsUpdate() == false) //UI의 IsUpdate가 false면 해당 UI를 삭제시킵니다.
		{
			MenuUITimer_ = 0.0f;
			FadeActor_->SetPosition(GetPosition() + GameEngineWindow::GetScale().Half());
			FadeActor_->FadeOut();

			ChildUI_->Death();
			ChildUI_ = nullptr;
		}
		else
		{
			return;//api 
		}
	}


	if (GameEngineInput::GetInst()->IsDown("Down") == true)
	{
		CurrentOrder_++;
		if (CurrentOrder_ > 5)
		{
			CurrentOrder_ = 0;
		}

	}

	if (GameEngineInput::GetInst()->IsDown("Up") == true)
	{
		CurrentOrder_--;
		if (CurrentOrder_ < 0)
		{
			CurrentOrder_ = 5;
		}

	}

	if (GameEngineInput::GetInst()->IsDown("X") == true && MenuUITimer_ > 0)
	{
		Off();
	}

	if (GameEngineInput::GetInst()->IsDown("Z") == true && MenuUITimer_ > 0)
	{
		switch (CurrentOrder_)
		{
		case 0: //포켓몬 메뉴
			if (ChildUI_ == nullptr)
			{
				FadeActor_->FadeOut();
				ChildUI_ = GetLevel()->CreateActor<PokemonMenu>(GetOrder() + 20, "PokemonMenu");
				ChildUI_->SetPosition(GetPosition());
				dynamic_cast<PokemonMenu*>(ChildUI_)->InitPokemonMenu();
			}
			break;
		case 1:
			if (ChildUI_ == nullptr)
			{
				FadeActor_->SetPosition(GetPosition() + GameEngineWindow::GetScale().Half());
				FadeActor_->FadeOut();
				ChildUI_ = GetLevel()->CreateActor<Bag>(GetOrder()+20);
				ChildUI_->SetPosition(GetPosition() + GameEngineWindow::GetScale().Half());
				dynamic_cast<Bag*>(ChildUI_)->SetPlayerItemList(PlayerRed::MainRed_->GetItemList());
				dynamic_cast<Bag*>(ChildUI_)->BagInit();
			}
			break;
		case 5:
			Off();
			return;
			break;
		default:
			break;
		}
	}


	MenuUITimer_ += GameEngineTime::GetDeltaTime();
}

void MenuUI::Render()
{
	for (size_t i = 0; i < 6; i++)
	{
		if (CurrentOrder_ != i)
		{
			MenuUIRenderer_[i]->Off();
			continue;
		}
		MenuUIRenderer_[i]->On();
	}
}
