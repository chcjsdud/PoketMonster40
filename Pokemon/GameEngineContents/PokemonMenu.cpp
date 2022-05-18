#include "PokemonMenu.h"
#include "UIEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Pokemon.h"
#include <GameEngineContentsCore/GameEngineContentFont.h>


PokemonMenu::PokemonMenu():
	BackgroundRenderer_(nullptr),
	PokemonNumber_(0),
	DialogRenderer_(nullptr),
	CancelRenderer_(nullptr),
	CurrentOrder_(0),
	RememberOrder_(0)
{
}

PokemonMenu::~PokemonMenu()
{
}

void PokemonMenu::Start()
{
	InitRenderer();
	PokemonNumber_ = 5;
	OnUI();

	////폰트 출력 테스트
	{
		Fonts = GetLevel()->CreateActor<GameEngineContentFont>();
		Fonts->SetPosition({ 16,540 });
		Fonts->ShowString("Please choose a pokemon");
	}

}

void PokemonMenu::Update()
{
	if (GameEngineInput::GetInst()->IsDown("Down") == true)
	{
		if (CurrentOrder_ >= PokemonNumber_)
		{
			CurrentOrder_ = 0;
		}
		else
		{
			CurrentOrder_++;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Up") == true)
	{
		if (CurrentOrder_ <= 0)
		{
			CurrentOrder_ = PokemonNumber_;
		}
		else
		{
			CurrentOrder_--;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Left") == true)
	{
		if (CurrentOrder_ != PokemonNumber_ && CurrentOrder_ != 0)
		{
			RememberOrder_ = CurrentOrder_;
			CurrentOrder_ = 0;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Right") == true)
	{
		if (CurrentOrder_== 0)
		{
			if (RememberOrder_ == 0)
			{
				RememberOrder_ = 1;
			}
			CurrentOrder_ = RememberOrder_;
		}
	}
}

void PokemonMenu::Render()
{
	//포켓몬 박스 이미지 선택 렌더링
	if (CurrentOrder_ == 0)
	{
		BoxRenderer_[0]->SetPivot({ 8,72 });
		BoxRenderer_[0]->SetImage("PoketmonMenu_15.bmp"); //커다란 박스
	}
	else
	{
		BoxRenderer_[0]->SetPivot({ 8,80 });
		BoxRenderer_[0]->SetImage("PoketmonMenu_14.bmp"); //커다란 박스
	}

	for (int i = 1; i < 6; i++)
	{
		if (CurrentOrder_ == i)
		{
			BoxRenderer_[i]->SetPivot({ 352,static_cast<float>(-60 + 96 * i) });
			BoxRenderer_[i]->SetImage("PoketmonMenu_13.bmp"); //작은 박스
		}
		else
		{
			BoxRenderer_[i]->SetPivot({ 352,static_cast<float>(-56 + 96 * i) });
			BoxRenderer_[i]->SetImage("PoketmonMenu_12.bmp"); //작은 박스
		}	
	}
	if (CurrentOrder_ == PokemonNumber_)
	{
		CancelRenderer_->SetPivot({ 732,522 });
		CancelRenderer_->SetImage("PoketmonMenu_11.bmp");
	}
	else
	{
		CancelRenderer_->SetPivot({ 732,530 });
		CancelRenderer_->SetImage("PoketmonMenu_10.bmp");
	}
}

void PokemonMenu::InitRenderer()
{
	//백그라운드
	BackgroundRenderer_ = CreateRenderer(static_cast<int>(UIRenderType::Background), RenderPivot::LeftTop);
	BackgroundRenderer_->SetImage("PoketmonMenu_22.bmp");

	//포켓몬 박스
	BoxRenderer_[0] = CreateRenderer(static_cast<int>(UIRenderType::Box), RenderPivot::LeftTop, { 8,80 });

	for (int i = 1; i < 6; i++)
	{
		BoxRenderer_[i] = CreateRenderer(static_cast<int>(UIRenderType::Box), RenderPivot::LeftTop, { 352,static_cast<float>(-56 + 96 * i) });
	}


	BoxRenderer_[0]->SetImage("PoketmonMenu_14.bmp"); //커다란 박스
	for (int i = 1; i < 6; i++)
	{
		BoxRenderer_[i]->SetImage("PoketmonMenu_12.bmp"); //작은 박스
	}

	for (int i = 0; i < 6; i++)
	{
		BoxRenderer_[i]->SetTransColor(RGB(255, 0, 255));
	}

	for (int i = 0; i < 6; i++)
	{
		BoxRenderer_[i]->Off();
	}

	//대화형 박스
	DialogRenderer_ = CreateRenderer(static_cast<int>(UIRenderType::Box), RenderPivot::LeftTop, { 8,520 });
	DialogRenderer_->SetImage("PoketmonMenu_16.bmp");
	DialogRenderer_->SetTransColor(RGB(255, 0, 255));

	//캔슬 버튼
	CancelRenderer_ = CreateRenderer(static_cast<int>(UIRenderType::Box), RenderPivot::LeftTop, { 732,530 });
	CancelRenderer_->SetImage("PoketmonMenu_10.bmp");
	CancelRenderer_->SetTransColor(RGB(255, 0, 255));

}

void PokemonMenu::GetPlayerPokemon()
{


	
}

void PokemonMenu::OnUI()
{
	for (int i = 0; i < PokemonNumber_; i++)
	{
		BoxRenderer_[i]->On();
	}
}




