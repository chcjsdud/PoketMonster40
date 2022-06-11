#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include "BattleInterface.h"
#include "BattleLevel.h"
#include "PokemonEngine.h"
#include "BattleEngine.h"
#include <GameEngineContentsCore/GameEngineContentFont.h>
#include "BattleUnitRenderer.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "BattleLevel.h"
#include "PlayerRed.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "Bag.h"
#include "PokemonMenu.h"


BattleInterface::BattleInterface()
	:TimeCheck(0.0f)
	, CurOrder(BattleOrder::None)
	, InterfaceImage(nullptr)
	, Select(nullptr)
	, MyHPUI(nullptr)
	, EnemyHPUI(nullptr)
	, MyHP(nullptr)
	, EnemyHP(nullptr)
	, EXP(nullptr)
	, BattleCommend(nullptr)
	, MainInterface(nullptr)
	, Level_(nullptr)
	, BattleUnit(nullptr)
	, OneTalk(false)
	, Fonts(nullptr)
	, PlayerEnd(false)
	, BattleFont_(nullptr)
	, SkillUIPos_(0)
	, BattleTimer_(0.0f)
	, PlayerName_(nullptr)
	, PlayerLevel_(nullptr)
	, PlayerHP_(nullptr)
	, PoeName_(nullptr)
	, PoeLevel_(nullptr)
	, HpRenderTimer_(0.0f)
	, PrevFoeHp_(0)
	, PrevPlayerHp_(0)
	, LerpFoeHp_(0)
	, LerpPlayerHp_(0)

{

}

BattleInterface::~BattleInterface()
{

}

void BattleInterface::Start()
{
	// 레벨 생성
	Level_ = dynamic_cast<BattleLevel*>(GetLevel());
	// 폰트 생성
	BattleFont_ = Level_->CreateActor<GameEngineContentFont>(10);
	BattleFont_->SetPosition({ 50, 485 });
	{

		GameEngineContentFont* index = nullptr;
		index = Level_->CreateActor<GameEngineContentFont>(10);
		index->SetPosition({ 50, 485 });
		AllSkillFont_.push_back(index);
		index = Level_->CreateActor<GameEngineContentFont>(10);
		index->SetPosition({ 350, 485 });
		AllSkillFont_.push_back(index);
		index = Level_->CreateActor<GameEngineContentFont>(10);
		index->SetPosition({ 50, 550 });
		AllSkillFont_.push_back(index);
		index = Level_->CreateActor<GameEngineContentFont>(10);
		index->SetPosition({ 350, 550 });
		AllSkillFont_.push_back(index);
	}
	// UI 폰트 
	{
		PlayerName_ = Level_->CreateActor<GameEngineContentFont>(10);
		PlayerName_->SetPosition({ 570 , 312 });
		PlayerName_->SetSize(0.85f);
		PlayerLevel_ = Level_->CreateActor<GameEngineContentFont>(10);
		PlayerLevel_->SetPosition({ 865 , 312 });
		PlayerLevel_->SetSize(0.85f);
		PlayerHP_ = Level_->CreateActor<GameEngineContentFont>(10);
		PlayerHP_->SetPosition({ 770 , 384 });
		PlayerHP_->SetSize(0.75f);
		PoeName_ = Level_->CreateActor<GameEngineContentFont>(10);
		PoeName_->SetPosition({ 85 , 56});
		PoeName_->SetSize(0.85f);
		PoeLevel_ = Level_->CreateActor<GameEngineContentFont>(10);
		PoeLevel_->SetPosition({ 380 , 56 });
		PoeLevel_->SetSize(0.85f);

	}
	// 키 생성
	GameEngineInput::GetInst()->CreateKey("SLeft", VK_LEFT);
	GameEngineInput::GetInst()->CreateKey("SRight", VK_RIGHT);
	GameEngineInput::GetInst()->CreateKey("SDown", VK_DOWN);
	GameEngineInput::GetInst()->CreateKey("SUp", VK_UP);
	GameEngineInput::GetInst()->CreateKey("SSelect", 'Z');
	GameEngineInput::GetInst()->CreateKey("SCancel", 'X');
	GameEngineInput::GetInst()->CreateKey("StartBattlePage", 'H');
	//

	InterfaceImage = CreateRenderer("Battle_Select.bmp", 6);
	InterfaceImage->Off();
	Select = CreateRenderer("Select.bmp", 8);
	Select->Off();

	EnemyHPUI = CreateRenderer("EnemyHPBackground4.bmp", 2);
	EnemyHPUI->Off();
	EnemyHP = CreateRenderer("EnemyHPBar4.bmp", 3,RenderPivot::LeftTop);
	EnemyHP->Off();
	MyHPUI = CreateRenderer("FriendlyHPBackground4.bmp", 2);
	MyHPUI->Off();
	MyHP = CreateRenderer("FriendlyHPBar4.bmp", 3,RenderPivot::LeftTop);
	MyHP->Off();
	EXP = CreateRenderer("FriendlyHPExp4.bmp", 3);
	EXP->Off();
	BattleCommend = CreateRenderer("BattleCommend4.bmp", 7);
	//Player = CreateRenderer("Player.bmp",0);

	//=========랜더러 위치 설정==========//
	Select->SetPivot({ -190.0f, -25.0f });

	MyHPUI->SetPivot({ 0.0f,-170.0f });
	EnemyHPUI->SetPivot({ -450.0f,-430.0f });
	EnemyHP->SetPivot({ -502.0f,-436.0f });
	MyHP->SetPivot({ -16.0f, -180.0f });
	EXP->SetPivot({ 48.0f,-170.0f });
	BattleCommend->SetPivot({ -240.0f,0.0f });
	BattleCommend->Off();//배틀커맨드는 Fight상태일때만

	//동원씨 도움 RegistActor=이미 만들어진 Actor를 Level에 등록
	GetLevel()->RegistActor("BattleInterface", this);
	//김예나:테스트 코드
	BattleUnit = dynamic_cast<BattleUnitRenderer*>(Level_->FindActor("BattleUnitRenderer"));
	Fonts = Level_->CreateActor<GameEngineContentFont>(8);
	Fonts->SetPosition({ 50, 485 });

	//HP정보 업데이트
	PrevPlayerHp_ = 19;
	PrevFoeHp_ = 19;
	LerpFoeHp_ = 19.0f;
	LerpPlayerHp_ = 19.0f;
}

void BattleInterface::Render()
{
	HPChangeAnimation();
	HPRenderUpdate();
}

void BattleInterface::Update()
{

	//if (!(Level_->BState_ == BattleState::SelecetPage) || !(Level_->CurrentSelect_ == BattleOrder::Fight))
	//{
	//	for (auto& Font : AllSkillFont_)
	//	{
	//		Font->ClearCurrentFonts();
	//	}
	//}

	//HP (Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetHp())
	//Poe (Level_->BattleData_->GetCurrentPoePokemon()->GetPokemon()->GetInfo()->GetHp())

	TimeCheck += (GameEngineTime::GetDeltaTime() * 2.0f);

	if (Level_->BState_ != BattleState::Openning)
	{
		if (!PlayerName_->IsRendererFont())
		{
			PlayerName_->ShowString(Level_->PlayerCurrentPokemon_->GetPokemon()->GetInfo()->GetNameConstRef() + (Level_->PlayerCurrentPokemon_->GetPokemon()->GetInfo()->GetGender() ? "[" : "]"), true);
			PlayerLevel_->ShowString(std::to_string(Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetMyLevel()), true);
			PlayerHP_->ShowString(std::to_string(Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetHp())
				+ "/ " + std::to_string(Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetMaxHp()), true);
		}

		if (!PoeName_->IsRendererFont())
		{
			PoeName_->ShowString(Level_->PoeCurrentPokemon_->GetPokemon()->GetInfo()->GetNameConstRef() + (Level_->PoeCurrentPokemon_->GetPokemon()->GetInfo()->GetGender() ? "[" : "]"), true);
			PoeLevel_->ShowString(std::to_string(Level_->BattleData_->GetCurrentPoePokemon()->GetPokemon()->GetInfo()->GetMyLevel()), true);
		}
		//MyHPUI->Is
	}



	if (BattleUnit->GetPlayerStop() == true && OneTalk == false)
	{
		//김예나:플레이어 멈출시 폰트출력 테스트
		//Fonts->ShowString("Wild NAME\\is appear!!\\Go!!\\NAME!!", false);
		StartTalk();
		OneTalk = true;
		//그 다음에 추가 폰트로 "가라 꼬부기!" 출력후 꼬부기 출현 + 배틀커맨드 이때 출현
	}

	{
		// 폰트 출력이 완료되고 키입력 대기
		if (Fonts->IsWait())
		{
			// Z 키 입력시 다음 문장 출력
			if (GameEngineInput::GetInst()->IsDown("Z") == true)
			{
				EnemyHPUI->On();
				EnemyHP->On();
				// 다음 문장 출력 함수
				Fonts->NextString();
			}
		}
		// 다음 문장이 없을 때 == 끝났을 때
		if (Fonts->IsEnd())
		{
			// 모든 대화가 끝났을 때 z 키누르면 
			if (GameEngineInput::GetInst()->IsDown("Z") == true)
			{
				PlayerEnd = true;
				Fonts->EndFont();
			}
		}
	}


	BattleTimer_ += GameEngineTime::GetDeltaTime();

	UIUpdate();

}

void BattleInterface::ShowAndCheckSkillPos()
{
	switch (SkillUIPos_)
	{
	case 0:
		Select->SetPivot({ -680.0f,-30.0f });
		break;
	case 1:
		Select->SetPivot({ -380.0f,-30.0f });
		break;
	case 2:
		Select->SetPivot({ -680.0f,35.0f });
		break;
	case 3:
		Select->SetPivot({ -380.0f,35.0f });
		break;
	default:
		break;
	}

	if (GameEngineInput::GetInst()->IsDown("SDown"))
	{
		switch (SkillUIPos_)
		{
		case 0:
			SkillUIPos_ = 2;
			break;
		case 1:
			SkillUIPos_ = 3;
			break;
		default:
			break;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("SUp"))
	{
		switch (SkillUIPos_)
		{
		case 2:
			SkillUIPos_ = 0;
			break;
		case 3:
			SkillUIPos_ = 1;
			break;
		default:
			break;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("SLeft"))
	{
		switch (SkillUIPos_)
		{
		case 1:
			SkillUIPos_ = 0;
			break;
		case 3:
			SkillUIPos_ = 2;
			break;
		default:
			break;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("SRight"))
	{
		switch (SkillUIPos_)
		{
		case 0:
			SkillUIPos_ = 1;
			break;
		case 2:
			SkillUIPos_ = 3;
			break;
		default:
			break;
		}
	}

	Level_->CurrentSelect_ = CurOrder;
	if (GameEngineInput::GetInst()->IsDown("SSelect"))
	{
		switch (CurOrder)
		{
		case BattleOrder::Fight:
		{
			BattleUnit->SetFighting(true);
			InterfaceImage->Off();
			BattleCommend->Off();
			Select->Off();

			if (Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetSkill().size() == 0)
			{
				MsgBoxAssert("스킬이 없습니다")
			}
			Level_->StartBattlePage(Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetSkill()[SkillUIPos_]->GetInfo()
				, RandomPoeSkill(Level_->GetBattleData()->GetCurrentPoePokemon()->GetPokemon()));

			for (auto& Font : AllSkillFont_)
			{
				Font->ClearCurrentFonts();
			}
			Select->Off();
			CurOrder = BattleOrder::None;
		}
		break;
		case BattleOrder::Pokemon:
			break;
		case BattleOrder::Bag:
			break;
		case BattleOrder::Run:
			break;
		default:
			break;
		}

		}
	else if (GameEngineInput::GetInst()->IsDown("SCancel"))
	{
		BattleCommend->Off();
		Select->SetPivot({ -190.0f,-25.0f });
		CurOrder = BattleOrder::None;
		Level_->CurrentSelect_ = CurOrder;

		for (auto& SkillFont : AllSkillFont_)
		{
			SkillFont->ClearCurrentFonts();
		}
	}

}

PokemonSkillInfo* BattleInterface::RandomPoeSkill(Pokemon* _Pokemon)
{
	if (_Pokemon->GetInfo()->GetSkill().size() == 0)
	{
		MsgBoxAssert("적 스킬이 Null입니다")
	}
	else
	{
		return _Pokemon->GetInfo()->GetSkill()[GameEngineRandom::GetRandom()->RandomInt(0, (int)(_Pokemon->GetInfo()->GetSkill().size()) - 1)]->GetInfo();
	}
	return nullptr;
}


void BattleInterface::ShowPokemonSkill(Pokemon* _Pokemon)
{
	std::vector<PokemonSkill*>& Skill = _Pokemon->GetInfo()->GetSkill();

	for (int i = 0; i < 4; i++)
	{
		if (AllSkillFont_[i]->IsRendererFont())
		{
			return;
		}

		for (int i = 0; i < 4; i++)
		{
			if (Skill.size() > i)
			{
				AllSkillFont_[i]->ShowString(Skill[i]->GetInfo()->GetNameConstRef(), true);
			}
			else
			{
				AllSkillFont_[i]->ShowString("-");
			}
		}
	}

}

bool BattleInterface::BattleKey()
{
	if (Level_->DoingSkillAnimation_ == true && (BattleUnit->GetMyAniTurn() == false || BattleUnit->GetPoeAniTurn() == false))
	{
		return false;
	}
	if (GameEngineInput::GetInst()->IsDown("SSelect") && BattleTimer_ > 0)
	{
		BattleTimer_ = 0;
		if (BattleFont_->IsEnd() || !BattleFont_->IsRendererFont())
		{
			BattleFont_->EndFont();
			//Level_->EndFont_ = true;
			return true;
		}
	}
	else if (!BattleFont_->IsRendererFont())
	{
		return true;
	}
	return false;
}

void BattleInterface::ShowUsedSkillString(const std::string& _AttPokemon, const std::string& _AttSkill)
{
	BattleFont_->EndFont();
	BattleFont_->ShowString(_AttPokemon + " Used\\" + _AttSkill + "!");
	Level_->EndFont_ = false;
}

void BattleInterface::ShowPoeFaintString(const std::string& _PoePokemon)
{
	BattleFont_->EndFont();
	BattleFont_->ShowString("Poe " + _PoePokemon + "\\fainted!");
	Level_->EndFont_ = false;
}

void BattleInterface::ShowPlayerFaintString(const std::string& _PlayerPokemon)
{
	BattleFont_->EndFont();
	BattleFont_->ShowString(_PlayerPokemon + " is\\fainted!");
	Level_->EndFont_ = false;
}


void BattleInterface::ShowSupperEffectString()
{
	BattleFont_->EndFont();
	BattleFont_->ShowString("It's Supe\\effective!");
	Level_->EndFont_ = false;
}

void BattleInterface::ShowCriticalHitString()
{
	BattleFont_->EndFont();
	BattleFont_->ShowString("A critical hit!");
	Level_->EndFont_ = false;
}

void BattleInterface::ShowNotEffective()
{
	BattleFont_->EndFont();
	BattleFont_->ShowString("It's not Very\\effective;");
	Level_->EndFont_ = false;
}

void BattleInterface::ShowFailed()
{
	BattleFont_->EndFont();
	BattleFont_->ShowString("But it failed!");
	Level_->EndFont_ = false;
}

void BattleInterface::ShowRankUpAndDown(const std::string& _Pokemon, PokemonAbility _Ability, int _Rank)
{
	BattleFont_->EndFont();
	std::string Rankfont = _Pokemon;
	Rankfont += " is\\";
	Rankfont += AbilityString(_Ability);
	Rankfont += RankString(_Rank);
	BattleFont_->ShowString(Rankfont);

	Level_->EndFont_ = false;
}

void BattleInterface::ShowGetEXP(const std::string& _PlayerPokemon, int _EXP)
{
	BattleFont_->EndFont();
	BattleFont_->ShowString(_PlayerPokemon + "gained\\" + std::to_string(_EXP) + " EXP. Points!");
	Level_->EndFont_ = false;
}
void BattleInterface::ShowChangePokemon(const std::string& _Poe,const std::string& _PoePokemon)
{
	BattleFont_->EndFont();
	BattleFont_->ShowString(_Poe + " sent\\out " + _PoePokemon + "!");
	Level_->EndFont_ = false;
}
void BattleInterface::ShowLevelUp(const std::string& _PlayerPokemon, int _Lv)
{
	BattleFont_->EndFont();
	BattleFont_->ShowString(_PlayerPokemon + "grew to\\LV. " + std::to_string(_Lv) + "!");
	Level_->EndFont_ = false;
}

std::string BattleInterface::AbilityString(PokemonAbility _Ability)
{
	switch (_Ability)
	{
	case PokemonAbility::Att:
		return "Attack";
		break;
	case PokemonAbility::Def:
		return "Defense";
		break;
	case PokemonAbility::SpAtt:
		return "Special Attack";
		break;
	case PokemonAbility::SpDef:
		return "Special Defense";
		break;
	case PokemonAbility::Speed:
		return "Speed";
		break;
	case PokemonAbility::Accuracy:
		return "Accuracy";
		break;
	case PokemonAbility::Evasion:
		return "Evasion";
		break;
	default:
		break;
	}
	return "Null";
}

std::string BattleInterface::RankString(int _Rank)
{
	switch (_Rank)
	{
	case 1:
		return " rose!";
		break;
	case 2:
		return " sharply rose!";
		break;
	case 3:
		return " rose drastically!";
		break;
	case -1:
		return " fell!";
		break;
	case -2:
		return " harshly fell!";
		break;
	case -3:
		return " severely fell!";
		break;
	}
	return "Null";
}



bool BattleInterface::MoveKey()
{
	if (ChildUI_ != nullptr)
	{
		return false;
	}
	if (BattleTimer_ <= 0.1f)
	{
		return false;
	}
	if (CurOrder == BattleOrder::Fight)
	{
		ShowPokemonSkill(Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon());
		ShowAndCheckSkillPos();
	}

	if (InterfaceImage->IsUpdate() == true)
	{
		if ((Select->GetPivot().x == -190.0f && Select->GetPivot().y == -25.0f) && true == GameEngineInput::GetInst()->IsDown("SDown"))
		{	//Fight에서 Pokemon으로
			Select->SetPivot({ -190.0f,35.0f });
		}

		if ((Select->GetPivot().x == -190.0f && Select->GetPivot().y == 35.0f) && true == GameEngineInput::GetInst()->IsDown("SUp"))
		{	//Pokemon에서 Fight로
			Select->SetPivot({ -190.0f,-25.0f });
		}

		if ((Select->GetPivot().x == -190.0f && Select->GetPivot().y == -25.0f) && true == GameEngineInput::GetInst()->IsDown("SRight"))
		{	//Fight에서 Bag으로
			Select->SetPivot({ 30.0f,-25.0f });
		}

		if ((Select->GetPivot().x == 30.0f && Select->GetPivot().y == -25.0f) && true == GameEngineInput::GetInst()->IsDown("SLeft"))
		{	//Bag에서 Fight로
			Select->SetPivot({ -190.0f,-25.0f });
		}

		if ((Select->GetPivot().x == 30.0f && Select->GetPivot().y == -25.0f) && true == GameEngineInput::GetInst()->IsDown("SDown"))
		{	//Bag에서 Run으로
			Select->SetPivot({ 30.0f,35.0f });
		}

		if ((Select->GetPivot().x == 30.0f && Select->GetPivot().y == 35.0f) && true == GameEngineInput::GetInst()->IsDown("SUp"))
		{	//Run에서 Bag으로
			Select->SetPivot({ 30.0f,-25.0f });
		}

		if ((Select->GetPivot().x == -190.0f && Select->GetPivot().y == 35.0f) && true == GameEngineInput::GetInst()->IsDown("SRight"))
		{	//Pokemon에서 Run으로
			Select->SetPivot({ 30.0f,35.0f });
		}

		if ((Select->GetPivot().x == 30.0f && Select->GetPivot().y == 35.0f) && true == GameEngineInput::GetInst()->IsDown("SLeft"))
		{	//Run에서 Pokemon으로
			Select->SetPivot({ -190.0f,35.0f });
		}


		{
			SelectOrder();
			OrderCheck();
		}


	}

	// 장중혁 : Debug
	if (GameEngineInput::GetInst()->IsDown("StartBattlePage"))
	{
		return true;
	}
	return false;
	//
}

void BattleInterface::DoomChit()
{
	if ((int)TimeCheck % 2 == 0)
	{
		MyHPUI->SetPivot({ 0.0f,-174.0f });
		MyHP->SetPivot({ -16.0f, -184.0f });
		EXP->SetPivot({ 48.0f,-174.0f });
		PlayerName_->SetPosition({ 570 ,  312 - 4 });
		PlayerLevel_->SetPosition({ 865 , 312 - 4 });
		PlayerHP_->SetPosition({ 770 , 384 - 4});

	}

	if ((int)TimeCheck % 2 == 1)
	{
		MyHPUI->SetPivot({ 0.0f,-170.0f });
		MyHP->SetPivot({ -16.0f, -180.0f });
		EXP->SetPivot({ 48.0f,-170.0f });
		PlayerName_->SetPosition({570 , 312 });
		PlayerLevel_->SetPosition({ 865 , 312 });
		PlayerHP_->SetPosition({ 770 , 384 });
	}
}

void BattleInterface::OrderCheck()
{
	switch (CurOrder)
	{
	case BattleOrder::Fight:
		BattleCommend->On();
		break;
	case BattleOrder::Pokemon:
		break;
	case BattleOrder::Bag:
		break;
	case BattleOrder::Run:
		break;
	default:
		break;
	}
}

void BattleInterface::SelectOrder()
{
	if (ChildUI_ != nullptr)
	{
		return;
	}
	if (InterfaceImage->IsUpdate() == true)
	{
		if ((Select->GetPivot().x == -190.0f && Select->GetPivot().y == -25.0f) && true == GameEngineInput::GetInst()->IsDown("SSelect"))
		{	//싸우다 선택

			CurOrder = BattleOrder::Fight;
		}

		if ((Select->GetPivot().x == -190.0f && Select->GetPivot().y == 35.0f) && true == GameEngineInput::GetInst()->IsDown("SSelect"))
		{	//포켓몬 선택
			CurOrder = BattleOrder::Pokemon;

			if (nullptr == ChildUI_)
			{
				ChildUI_ = GetLevel()->CreateActor<PokemonMenu>(60, "PokemonMenu");
				ChildUI_->SetPosition(float4(0,0));
				dynamic_cast<PokemonMenu*>(ChildUI_)->InitPokemonMenu();
			}
		}

		if ((Select->GetPivot().x == 30.0f && Select->GetPivot().y == -25.0f) && true == GameEngineInput::GetInst()->IsDown("SSelect"))
		{	
			//가방 선택
			CurOrder = BattleOrder::Bag;

			if (nullptr == ChildUI_)
			{
				ChildUI_ = GetLevel()->CreateActor<Bag>(50);
				ChildUI_->SetPosition(float4(0,0)+GameEngineWindow::GetScale().Half());
				dynamic_cast<Bag*>(ChildUI_)->SetPlayerItemList(PlayerRed::MainRed_->GetItemList());
				dynamic_cast<Bag*>(ChildUI_)->BagInit();
			}
		}

		if ((Select->GetPivot().x == 30.0f && Select->GetPivot().y == 35.0f) && true == GameEngineInput::GetInst()->IsDown("SSelect"))
		{
			CurOrder = BattleOrder::Run;
		}
	}
}

void BattleInterface::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (BattleUnit == nullptr)
	{
		BattleUnit = dynamic_cast<BattleUnitRenderer*>(Level_->FindActor("BattleUnitRenderer"));
	}
	OneTalk = false;

}

void BattleInterface::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

	Reset();

}

void BattleInterface::StartTalk()
{
	Fonts->ClearCurrentFonts();
	Fonts->ShowString("Wild " + Level_->GetBattleData()->GetCurrentPoePokemon()->GetPokemon()->GetInfo()->GetNameConstRef() + "\\is appear!!\\Go!!\\"
		+ Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetNameConstRef() + "!!", false);
}


void BattleInterface::Reset()
{
	OneTalk = true;
	BattleUnit->SetPlayerStop(false);
	PlayerEnd = false;
	BattleCommend->Off();
	InterfaceImage->Off();
	Select->Off();
	MyHPUI->Off();
	EnemyHPUI->Off();
	MyHP->Off();
	EnemyHP->Off();
	EXP->Off();
	BattleFont_->ClearCurrentFonts();
	Fonts->ClearCurrentFonts();
	for (auto Iter : AllSkillFont_)
	{
		Iter->ClearCurrentFonts();
	}

	Level_->CurrentSelect_ = BattleOrder::None;
	CurOrder = Level_->CurrentSelect_;
	Select->SetPivot({ -190.0f,-25.0f });

	// 스킬 마우스포인터
	SkillUIPos_ = 0;


	PlayerName_->EndFont();
	 PlayerLevel_->EndFont();
	 PlayerHP_->EndFont();
	 PoeName_->EndFont();
	 PoeLevel_->EndFont();
	 BattleFont_->EndFont();
		 Fonts->EndFont();
}

void BattleInterface::UIUpdate()
{
	if (ChildUI_ != nullptr) // UI창이 뜰 경우
	{
		if (ChildUI_->IsUpdate() == false) //UI의 IsUpdate가 false면 해당 UI를 삭제시킵니다.
		{
			ChildUI_->Death();
			ChildUI_ = nullptr;
		}
	}
}

void BattleInterface::HPChangeAnimation()
{
	//적 Hp변화를 감지하고 HP 보간 진행
	int FoeHp = Level_->BattleData_->GetCurrentPoePokemon()->GetPokemon()->GetInfo()->GetHp();
	if (PrevFoeHp_ != FoeHp)
	{
		HpRenderTimer_ += GameEngineTime::GetDeltaTime();
		LerpFoeHp_ = GameEngineMath::LerpLimit(static_cast<float>(PrevFoeHp_), static_cast<float>(FoeHp), HpRenderTimer_);

		//보간값이 변화된 적 HP와 같아지면 보간 종료
		if (static_cast<int>(LerpFoeHp_) == FoeHp)
		{
			PrevFoeHp_ = FoeHp;
			HpRenderTimer_ = 0.0f;
		}
	}

	//플레이어 Hp변화를 감지하고 HP 보간 진행
	int PlayerHP = Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetHp();
	if (PrevPlayerHp_ != PlayerHP)
	{
		HpRenderTimer_ += GameEngineTime::GetDeltaTime();
		LerpPlayerHp_ = GameEngineMath::LerpLimit(static_cast<float>(PrevPlayerHp_), static_cast<float>(PlayerHP), HpRenderTimer_);

		//보간값이 변화된 적 HP와 같아지면 보간 종료
		if (static_cast<int>(LerpPlayerHp_) == PlayerHP)
		{
			PrevPlayerHp_ = PlayerHP;
			HpRenderTimer_ = 0.0f;
		}
	}
}

void BattleInterface::HPRenderUpdate()
{

	//적 Hp 렌더링
	{
		float HpRatio = LerpFoeHp_ / static_cast<float>(Level_->BattleData_->GetCurrentPoePokemon()->GetPokemon()->GetInfo()->GetMaxHp());
		float HpXScale = GameEngineImageManager::GetInst()->Find("PoketmonMenu_Hp1.bmp")->GetScale().x * HpRatio;
		if (HpRatio > 0.5f)
		{
			EnemyHP->SetImage("PoketmonMenu_Hp1.bmp");
		}
		else if (HpRatio >= 0.2f && HpRatio <= 0.5f)
		{
			EnemyHP->SetImage("PoketmonMenu_Hp2.bmp");
		}
		else
		{
			EnemyHP->SetImage("PoketmonMenu_Hp3.bmp");
		}
		EnemyHP->SetScale({ HpXScale ,EnemyHP->GetScale().y });
	}
	

	//플레이어 HP 렌더링
	{
		float HpRatio = LerpPlayerHp_ / static_cast<float>(Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetMaxHp());
		float HpXScale = GameEngineImageManager::GetInst()->Find("PoketmonMenu_Hp1.bmp")->GetScale().x * HpRatio;
		if (HpRatio > 0.5f)
		{
			MyHP->SetImage("PoketmonMenu_Hp1.bmp");
		}
		else if (HpRatio >= 0.2f && HpRatio <= 0.5f)
		{
			MyHP->SetImage("PoketmonMenu_Hp2.bmp");
		}
		else
		{
			MyHP->SetImage("PoketmonMenu_Hp3.bmp");
		}
		MyHP->SetScale({ HpXScale ,MyHP->GetScale().y });
	}
	

}
