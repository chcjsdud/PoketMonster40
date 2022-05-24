#include "PokemonMenu.h"
#include "UIEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Pokemon.h"
#include <GameEngineContentsCore/GameEngineContentFont.h>
#include "PokemonInfoManager.h"
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngine.h>


PokemonMenu::PokemonMenu():
	BackgroundRenderer_(nullptr),
	PokemonNumber_(0),
	DialogRenderer_(nullptr),
	CancelRenderer_(nullptr),
	CurrentOrder_(0),
	RememberOrder_(0),
	CurState_(PokemonMenuType::SelectPokemon),
	CurTickTime_(0),
	IsJump_(0)
{
	PokemonRenderer_.resize(6);
}

PokemonMenu::~PokemonMenu()
{
}

void PokemonMenu::Start()
{
	//NullImage_Ani 슬라이스
	GameEngineImage* NullImage = GameEngineImageManager::GetInst()->Find("NullImage_Ani.bmp");
	NullImage->Cut({ 32,32 });

	InitRenderer();
	OnUI();
	

	

}

void PokemonMenu::Update()
{
	UpdateState();	


}

void PokemonMenu::Render()
{
	//포켓몬 렌더 피벗 정보 업데이트
	{
		//포켓몬
		{
			PokemonRenderer_[0]->SetPivot({ 65,200 });
			for (size_t i = 1; i < PokemonNumber_; i++)
			{
				PokemonRenderer_[i]->SetPivot({ 406, static_cast<float>(40 + 96 * i) });
			}
		}

		//체력
		{

		}
		
	}
	//포켓몬 이미지 선택 렌더링
	if (CurrentOrder_ == 0) //선택된 경우
	{
		BoxRenderer_[0]->SetPivot({ 8,72 });
		BoxRenderer_[0]->SetImage("PoketmonMenu_15.bmp"); //커다란 박스ㅇ
	}
	
	else
	{
		BoxRenderer_[0]->SetPivot({ 8,80 });
		BoxRenderer_[0]->SetImage("PoketmonMenu_14.bmp"); //커다란 박스
	}

	for (int i = 1; i < 6; i++)
	{
		if (CurrentOrder_ == i) //선택된 경우
		{
			BoxRenderer_[i]->SetPivot({ 352,static_cast<float>(-60 + 96 * i) });
			BoxRenderer_[i]->SetImage("PoketmonMenu_13.bmp"); //작은 박스
		}
		else //선택 안된 경우
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

	//Hp 렌더링
	float HpRatio = static_cast<float>(PokemonList_[0]->GetHp()) / static_cast<float>(PokemonList_[0]->GetMaxHp());
	float HpXScale = GameEngineImageManager::GetInst()->Find("PoketmonMenu_Hp1.bmp")->GetScale().x * HpRatio;
	if (HpRatio > 0.5f)
	{
		HpRenderer_[0]->SetImage("PoketmonMenu_Hp1.bmp");
	}
	else if (HpRatio >= 0.2f && HpRatio <= 0.5f)
	{
		HpRenderer_[0]->SetImage("PoketmonMenu_Hp2.bmp");
	}
	else
	{
		HpRenderer_[0]->SetImage("PoketmonMenu_Hp3.bmp");
	}
	HpRenderer_[0]->SetScale({HpXScale ,HpRenderer_[0]->GetScale().y});
	for (size_t i = 1; i < PokemonNumber_; i++)
	{
		float HpRatio = static_cast<float>(PokemonList_[i]->GetHp()) / static_cast<float>(PokemonList_[i]->GetMaxHp());
		float HpXScale = GameEngineImageManager::GetInst()->Find("PoketmonMenu_Hp1.bmp")->GetScale().x * HpRatio;
		if (HpRatio > 0.5f)
		{
			HpRenderer_[i]->SetImage("PoketmonMenu_Hp1.bmp");
		}
		else if (HpRatio >= 0.2f && HpRatio <= 0.5f)
		{
			HpRenderer_[i]->SetImage("PoketmonMenu_Hp2.bmp");
		}
		else
		{
			HpRenderer_[i]->SetImage("PoketmonMenu_Hp3.bmp");
		}
		HpRenderer_[i]->SetScale({ HpXScale ,HpRenderer_[0]->GetScale().y });
	}



	//Curstate == SelectAction일때만 렌더
	if (CurState_ == PokemonMenuType::SelectAction)
	{
		switch (SelectActionOrder_)
		{
		case 0:
			MenuArrowRenderer_->SetPivot({ 610,370 });
			break;
		case 1:
			MenuArrowRenderer_->SetPivot({ 610,434 });
			break;
		case 2:
			MenuArrowRenderer_->SetPivot({ 610,498});
			break;
		case 3:
			MenuArrowRenderer_->SetPivot({ 610,562 });
			break;
		default:
			break;
		}
	}
	//LPPOINT mousePos; // 마우스 좌표를 저장할 변수 생성. POINT 자료형의 포인터형임.
	//mousePos = new POINT;
	//GetCursorPos(mousePos); // 바탕화면에서의 마우스 좌표를 가져옴
	//ScreenToClient(nullptr, mousePos);
	//int x = mousePos->x;
	//TextOut(GameEngine::BackBufferDC(), 100, 100, std::to_string(x).c_str(), std::to_string(x).length());
}



void PokemonMenu::ChangeState(PokemonMenuType _Type)
{
	if (CurState_ == _Type)
	{
		return;
	}

	switch (_Type)
	{
	case PokemonMenu::PokemonMenuType::SelectPokemon:
		SelectPokemonStart();
		break;
	case PokemonMenu::PokemonMenuType::SelectAction:
		SelectActionStart();
		break;
	case PokemonMenu::PokemonMenuType::SelectSwitch:
		SelectSwitchStart();
		break;
	default:
		break;
	}
	CurState_ = _Type;
}

void PokemonMenu::UpdateState()
{
	switch (CurState_)
	{
	case PokemonMenu::PokemonMenuType::SelectPokemon:
		SelectPokemonUpdate();
		break;
	case PokemonMenu::PokemonMenuType::SelectAction:
		SelectActionUpdate();
		break;
	case PokemonMenu::PokemonMenuType::SelectSwitch:
		SelectSwitchUpdate();
		break;
	default:
		break;
	}
}

void PokemonMenu::SelectPokemonStart()
{


	DialogRenderer_->On();
	DialogFont_->On();
	CancelRenderer_->On();
	SwitchFont_->Off();
	QuestionDialogRenderer_->Off();
	SelectDialogRenderer_->Off();
	MenuArrowRenderer_->Off();

	//퀘스쳔 폰트 제거
	{
		for (GameEngineContentFont* i : AllFonts_)
		{
			if (i == QuestionFont_)
			{
				AllFonts_.remove(i);
				break;
			}
		}
		QuestionFont_->ClearCurrentFonts();
	}


}

void PokemonMenu::SelectPokemonUpdate()
{
	if (GameEngineInput::GetInst()->IsDown("Down") == true)
	{
		if (CurrentOrder_ >= PokemonNumber_)
		{
			CurrentOrder_ = 0;
		}
		else
		{
			ResetJump();
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
			ResetJump();
			CurrentOrder_--;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Left") == true)
	{
		if (CurrentOrder_ != PokemonNumber_ && CurrentOrder_ != 0)
		{
			ResetJump();
			RememberOrder_ = CurrentOrder_;
			CurrentOrder_ = 0;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Right") == true)
	{
		if (CurrentOrder_ == 0)
		{
			if (RememberOrder_ == 0)
			{
				ResetJump();
				RememberOrder_ = 1;
			}
			ResetJump();
			CurrentOrder_ = RememberOrder_;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Z") == true)
	{
		ChangeState(PokemonMenuType::SelectAction);
	}

	if (GameEngineInput::GetInst()->IsDown("X") == true)
	{
		ChangeState(PokemonMenuType::SelectPokemon);
	}
}

void PokemonMenu::SelectActionStart()
{
	DialogRenderer_->Off();
	DialogFont_->Off();
	CancelRenderer_->Off();
	SwitchFont_->Off();
	QuestionDialogRenderer_->On();
	SelectDialogRenderer_->On();
	MenuArrowRenderer_->On();
	//폰트 초기화
	{
		QuestionFont_ = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
		QuestionFont_->SetPosition({ 16,540 });
		QuestionFont_->ShowString("What do " + PokemonList_[CurrentOrder_]->GetNameCopy(), true);
		AllFonts_.push_back(QuestionFont_);
	}

	SelectActionOrder_ = 0;
	MenuArrowRenderer_->SetPivot({ 610,370 });
}

void PokemonMenu::SelectActionUpdate()
{
	if (GameEngineInput::GetInst()->IsDown("X") == true)
	{
		ChangeState(PokemonMenuType::SelectPokemon);
		//ChangeHp(0, 1);
	}

	if (GameEngineInput::GetInst()->IsDown("Z") == true)
	{
		switch (SelectActionOrder_)
		{
		case 1:
			ChangePokemonNumber_1 = CurrentOrder_;
			ChangeState(PokemonMenuType::SelectSwitch);
			break;
		case 3:
			ChangeState(PokemonMenuType::SelectPokemon);
			break;

		default:
			break;
		}

		//ChangeHp(0, 1);
	}

	//위 아래 조작
	if (GameEngineInput::GetInst()->IsDown("Down") == true)
	{
		if (SelectActionOrder_ >= 3)
		{
			SelectActionOrder_ = 0;
		}
		else
		{
			SelectActionOrder_++;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Up") == true)
	{
		if (SelectActionOrder_ <= 0)
		{
			SelectActionOrder_ = 3;
		}
		else
		{
			SelectActionOrder_--;
		}
	}
}

void PokemonMenu::SelectSwitchStart()
{
	DialogRenderer_->On();
	CancelRenderer_->On();
	SwitchFont_->On();
	QuestionDialogRenderer_->Off();
	SelectDialogRenderer_->Off();
	MenuArrowRenderer_->Off();

	//퀘스쳔 폰트 제거
	{
		for (GameEngineContentFont* i : AllFonts_)
		{
			if (i == QuestionFont_)
			{
				AllFonts_.remove(i);
				break;
			}
		}
		QuestionFont_->ClearCurrentFonts();
	}
}

void PokemonMenu::SelectSwitchUpdate()
{
	if (GameEngineInput::GetInst()->IsDown("Down") == true)
	{
		if (CurrentOrder_ >= PokemonNumber_)
		{
			CurrentOrder_ = 0;
		}
		else
		{
			ResetJump();
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
			ResetJump();
			CurrentOrder_--;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Left") == true)
	{
		if (CurrentOrder_ != PokemonNumber_ && CurrentOrder_ != 0)
		{
			ResetJump();
			RememberOrder_ = CurrentOrder_;
			CurrentOrder_ = 0;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Right") == true)
	{
		if (CurrentOrder_ == 0)
		{
			if (RememberOrder_ == 0)
			{
				ResetJump();
				RememberOrder_ = 1;
			}
			ResetJump();
			CurrentOrder_ = RememberOrder_;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Z") == true)
	{
		ChangePokemonNumber_2 = CurrentOrder_;
		if (ChangePokemonNumber_1 != ChangePokemonNumber_2)
		{
			{
				//Info 변경
				PokemonInfo* temp = PokemonList_[ChangePokemonNumber_1];
				PokemonList_[ChangePokemonNumber_1] = PokemonList_[ChangePokemonNumber_2];
				PokemonList_[ChangePokemonNumber_2] = temp;
			}

			//Renderer 변경
			{
				GameEngineRenderer* temp = PokemonRenderer_[ChangePokemonNumber_1];
				PokemonRenderer_[ChangePokemonNumber_1] = PokemonRenderer_[ChangePokemonNumber_2];
				PokemonRenderer_[ChangePokemonNumber_2] = temp;
			}

		}
	}

	if (GameEngineInput::GetInst()->IsDown("X") == true)
	{
		ChangeState(PokemonMenuType::SelectPokemon);
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

	//질문형 대화형 박스
	QuestionDialogRenderer_ = CreateRenderer(static_cast<int>(UIRenderType::Box), RenderPivot::LeftTop, { 8,520 });
	QuestionDialogRenderer_->SetImage("DialogBox_PokemonMenu_Question.bmp");
	QuestionDialogRenderer_->SetTransColor(RGB(255, 0, 255));
	QuestionDialogRenderer_->Off();

	//선택형 대화형 박스
	SelectDialogRenderer_ = CreateRenderer(static_cast<int>(UIRenderType::Box), RenderPivot::LeftTop, { 580,326 });
	SelectDialogRenderer_->SetImage("DialogBox_PokemonMenu_Select.bmp");
	SelectDialogRenderer_->SetTransColor(RGB(255, 0, 255));
	SelectDialogRenderer_->Off();

	//캔슬 버튼
	CancelRenderer_ = CreateRenderer(static_cast<int>(UIRenderType::Box), RenderPivot::LeftTop, { 732,530 });
	CancelRenderer_->SetImage("PoketmonMenu_10.bmp");
	CancelRenderer_->SetTransColor(RGB(255, 0, 255));

	//포켓몬 아이콘
	PokemonRenderer_[0] = CreateRenderer(static_cast<int>(UIRenderType::Object), RenderPivot::BOT, { 65,200 });
	PokemonRenderer_[0]->CreateAnimation("Nullimage_Ani.bmp", "Null", 0, 1,0.1f,false);
	PokemonRenderer_[0]->ChangeAnimation("Null");
	PokemonRenderer_[0]->SetTransColor(RGB(255, 0, 255));
	PokemonRenderer_[0]->Off();

	for (int i = 1; i < 6; i++)
	{
		PokemonRenderer_[i] = CreateRenderer(static_cast<int>(UIRenderType::Object), RenderPivot::BOT, { 406,static_cast<float>(40 + 96 * i) });
		PokemonRenderer_[i]->CreateAnimation("Nullimage_Ani.bmp", "Null", 0, 1, 0.1f, false);
		PokemonRenderer_[i]->ChangeAnimation("Null");
		PokemonRenderer_[i]->SetTransColor(RGB(255, 0, 255));
		PokemonRenderer_[i]->Off();
	}

	//HP박스
	HpRenderer_[0] = CreateRenderer(static_cast<int>(UIRenderType::Object), RenderPivot::LeftTop, {128,236});
	HpRenderer_[0]->SetImage("PoketmonMenu_Hp1.bmp");
	HpRenderer_[0]->SetTransColor(RGB(255, 0, 255));

	for (int i = 1; i < 6; i++)
	{
		HpRenderer_[i] = CreateRenderer(static_cast<int>(UIRenderType::Object), RenderPivot::LeftTop, { 736,static_cast<float>( -24+ 96 * i) });
		HpRenderer_[i]->SetImage("PoketmonMenu_Hp1.bmp");
		HpRenderer_[i]->SetTransColor(RGB(255, 0, 255));
		HpRenderer_[i]->Off();
	}

	//성별
	GenderRenderer_	[0] = CreateRenderer(static_cast<int>(UIRenderType::Object), RenderPivot::LeftTop, { 268,186 });
	GenderRenderer_[0]->SetImage("PoketmonMenu_20.bmp");
	GenderRenderer_[0]->SetTransColor(RGB(255, 0, 255));

	for (int i = 1; i < 6; i++)
	{
		GenderRenderer_[i] = CreateRenderer(static_cast<int>(UIRenderType::Object), RenderPivot::LeftTop, { 636,static_cast<float>(+ 96 * i) });
		GenderRenderer_[i]->SetImage("PoketmonMenu_20.bmp");
		GenderRenderer_[i]->SetTransColor(RGB(255, 0, 255));
		GenderRenderer_[i]->Off();
	}

	//MenuArrow
	MenuArrowRenderer_ = CreateRenderer(static_cast<int>(UIRenderType::Object), RenderPivot::LeftTop, { 610,370 });
	MenuArrowRenderer_->SetImage("Bag_CurrentArrow.bmp");
	MenuArrowRenderer_->SetTransColor(RGB(255, 0, 255));
	MenuArrowRenderer_->Off();

}

void PokemonMenu::GetPlayerPokemon()
{

	//여기서 플레이어 리스트를 분해하고 포캐몬 개수만큼 PokemonNumber을 올려준다.
	{
		PokemonInfo* Charmander = PokemonInfoManager::GetInst().FindPokemonInfo("Charmander");
		PokemonInfo* Squirtle = PokemonInfoManager::GetInst().FindPokemonInfo("Squirtle"); //Bulbasaur
		PokemonInfo* Bulbasaur = PokemonInfoManager::GetInst().FindPokemonInfo("Bulbasaur");
		Charmander->PlusHp(-10);
		Squirtle->PlusHp(-50);
		Bulbasaur->PlusHp(-90);

		PokemonList_.push_back(Charmander);
		PokemonList_.push_back(Squirtle);
		PokemonList_.push_back(Bulbasaur);
		PokemonNumber_ = 3;

		//포켓몬 이름의 아이콘 애니메이션을 추가해 준다
		for (int i = 0; i < PokemonList_.size(); i++)
		{
			PokemonRenderer_[i]->CreateAnimation(PokemonList_[i]->GetMyIcon(), PokemonList_[i]->GetNameCopy(), 0, 1, 0.3f, true);
			PokemonRenderer_[i]->ChangeAnimation(PokemonList_[i]->GetNameCopy());
		}

		//포켓몬의 성별을 렌더러에 업데이트 해준다
		for (int i = 0; i < PokemonList_.size(); i++)
		{
			if (PokemonList_[i]->GetGender() == true) //수컷
			{
				GenderRenderer_[i]->SetImage("PoketmonMenu_20.bmp");
			}
			else
			{
				GenderRenderer_[i]->SetImage("PoketmonMenu_21.bmp");
			}
			
		}
	}
}

void PokemonMenu::OnUI()
{
	GetPlayerPokemon();
	InitFont();
	for (int i = 0; i < PokemonNumber_; i++)
	{
		BoxRenderer_[i]->On();
		PokemonRenderer_[i]->On();
		HpRenderer_[i]->On();
		GenderRenderer_[i]->On();
	}

}

void PokemonMenu::ChangeHp(int _PokemonIndex, int _value)
{
	PokemonInfo* CurPokemonInfo = PokemonList_[_PokemonIndex];
	CurPokemonInfo->PlusHp(_value);
	//현재 폰트 업데이트
	for (GameEngineContentFont* i : AllFonts_)
	{
		if (i == CurHpFonts_[_PokemonIndex])
		{
			AllFonts_.remove(i);
			break;
		}
	}
	CurHpFonts_[_PokemonIndex]->ClearCurrentFonts();

	GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
	if (_PokemonIndex == 0)
	{
		NewFonts->SetPosition({ 150,248 });
	}
	else
	{
		NewFonts->SetPosition({ 760,static_cast<float>(-16 + 96 * _PokemonIndex) });
	}
	NewFonts->ShowString(std::to_string(PokemonList_[_PokemonIndex]->GetHp()), true);

	AllFonts_.push_back(NewFonts);
	CurHpFonts_[_PokemonIndex] = NewFonts;
}

void PokemonMenu::InitFont()
{
	//첫번째 포켓몬 폰트
	{
		//이름
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 75,126 });
			NewFonts->ShowString(PokemonList_[0]->GetNameCopy(), true);
			AllFonts_.push_back(NewFonts);
		}

		//레벨
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 190,175 });
			NewFonts->ShowString(std::to_string(PokemonList_[0]->GetMyLevel()), true);
			AllFonts_.push_back(NewFonts);
		}

		//현재 체력
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 150,248 });
			NewFonts->ShowString(std::to_string(PokemonList_[0]->GetHp()), true);
			AllFonts_.push_back(NewFonts);
			CurHpFonts_.push_back(NewFonts);
		}

		//최대 체력
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 260,248 });
			NewFonts->ShowString(std::to_string(PokemonList_[0]->GetMaxHp()), true);
			AllFonts_.push_back(NewFonts);
		}

	}
	
	//2째 ~ 그뒤 포켓몬
	for (int i = 1; i < PokemonList_.size(); i++)
	{
		//PokemonRenderer_[i]->ChangeAnimation(PokemonList_[i]->GetNameCopy());
		//이름
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 416,static_cast<float>(-60 + 96 * i )});
			NewFonts->ShowString(PokemonList_[i]->GetNameCopy(), true);
			AllFonts_.push_back(NewFonts);
		}

		//레벨
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 540,static_cast<float>(-16 + 96 * i) });
			NewFonts->ShowString(std::to_string(PokemonList_[i]->GetMyLevel()), true);
			AllFonts_.push_back(NewFonts);
		}

		//현재 체력
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 760,static_cast<float>(-16 + 96 * i)});
			NewFonts->ShowString(std::to_string(PokemonList_[i]->GetHp()), true);
			AllFonts_.push_back(NewFonts);
			CurHpFonts_.push_back(NewFonts);
		}

		//최대 체력
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 870,static_cast<float>(-16 + 96 * i) });
			NewFonts->ShowString(std::to_string(PokemonList_[i]->GetMaxHp()), true);
			AllFonts_.push_back(NewFonts);
		}

	}
	//포켓몬을 골라주세요 폰트
	{
		DialogFont_ = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
		DialogFont_->SetPosition({ 16,540 });
		DialogFont_->ShowString("Choose a pokemon", true);
		AllFonts_.push_back(DialogFont_);
	}
	//swtich 문구
	{
		SwitchFont_ = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
		SwitchFont_->SetPosition({ 16,540});
		SwitchFont_->ShowString("Move to Where?", true);
		SwitchFont_->Off();
		AllFonts_.push_back(SwitchFont_);
	}

}

void PokemonMenu::UpdateFont()
{
		//첫번째 포켓몬 폰트
	{
		//이름
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 75,126 });
			NewFonts->ShowString(PokemonList_[0]->GetNameCopy(), true);
			AllFonts_.push_back(NewFonts);
		}

		//레벨
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 190,175 });
			NewFonts->ShowString(std::to_string(PokemonList_[0]->GetMyLevel()), true);
			AllFonts_.push_back(NewFonts);
		}

		//현재 체력
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 150,248 });
			NewFonts->ShowString(std::to_string(PokemonList_[0]->GetHp()), true);
			AllFonts_.push_back(NewFonts);
			CurHpFonts_.push_back(NewFonts);
		}

		//최대 체력
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 260,248 });
			NewFonts->ShowString(std::to_string(PokemonList_[0]->GetMaxHp()), true);
			AllFonts_.push_back(NewFonts);
		}

	}
	
	//2째 ~ 그뒤 포켓몬
	for (int i = 1; i < PokemonList_.size(); i++)
	{
		//PokemonRenderer_[i]->ChangeAnimation(PokemonList_[i]->GetNameCopy());
		//이름
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 416,static_cast<float>(-60 + 96 * i )});
			NewFonts->ShowString(PokemonList_[i]->GetNameCopy(), true);
			AllFonts_.push_back(NewFonts);
		}

		//레벨
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 540,static_cast<float>(-16 + 96 * i) });
			NewFonts->ShowString(std::to_string(PokemonList_[i]->GetMyLevel()), true);
			AllFonts_.push_back(NewFonts);
		}

		//현재 체력
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 760,static_cast<float>(-16 + 96 * i)});
			NewFonts->ShowString(std::to_string(PokemonList_[i]->GetHp()), true);
			AllFonts_.push_back(NewFonts);
			CurHpFonts_.push_back(NewFonts);
		}

		//최대 체력
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
			NewFonts->SetPosition({ 870,static_cast<float>(-16 + 96 * i) });
			NewFonts->ShowString(std::to_string(PokemonList_[i]->GetMaxHp()), true);
			AllFonts_.push_back(NewFonts);
		}

	}
	//포켓몬을 골라주세요 폰트
	{
		DialogFont_ = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
		DialogFont_->SetPosition({ 16,540 });
		DialogFont_->ShowString("Choose a pokemon", true);
		AllFonts_.push_back(DialogFont_);
	}
	//swtich 문구
	{
		SwitchFont_ = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(UIRenderType::Font));
		SwitchFont_->SetPosition({ 16,540});
		SwitchFont_->ShowString("Move to Where?", true);
		SwitchFont_->Off();
		AllFonts_.push_back(SwitchFont_);
	}
}

void PokemonMenu::IconJump(GameEngineRenderer* _Render)
{
	CurTickTime_ += GameEngineTime::GetDeltaTime();
	if (CurTickTime_ > 0.15f)
	{
		CurTickTime_ = 0;
		if (IsJump_ == true)
		{
			_Render->SetPivot({ _Render->GetPivot().x,_Render->GetPivot().y + 30});
			IsJump_ = false;	
		}
		else
		{
			_Render->SetPivot({ _Render->GetPivot().x,_Render->GetPivot().y - 30 });
			IsJump_ = true;
		}
	}
}

void PokemonMenu::ResetJump()
{
	IsJump_ = false;
	CurTickTime_ = 0;
}




