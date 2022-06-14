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
#include "PokemonSkill.h"


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
	, PPFont_(nullptr)
	, MaxPPFont_(nullptr)
	, TypeFont_(nullptr)
	, PrevExp_(0)
	, LerpExp_(0.0f)
	, ExpRenderTimer_(0.0f)
	, ChildUI_(nullptr)
	, BattleStatus_(nullptr)

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
		PoeName_->SetPosition({ 85 , 56 });
		PoeName_->SetSize(0.85f);
		PoeLevel_ = Level_->CreateActor<GameEngineContentFont>(10);
		PoeLevel_->SetPosition({ 380 , 56 });
		PoeLevel_->SetSize(0.85f);

	}
	// 레벨업 폰트
	{
		GameEngineContentFont* index = nullptr;
		index = Level_->CreateActor<GameEngineContentFont>(12);
		index->SetPosition({ 820, 262 });
		index->Off();
		AllLevelUpFont_.push_back(index);

		index = Level_->CreateActor<GameEngineContentFont>(12);
		index->SetPosition({ 820, 262 + 60});
		index->Off();
		AllLevelUpFont_.push_back(index);

		index = Level_->CreateActor<GameEngineContentFont>(12);
		index->SetPosition({ 820, 262 + 60 * 2});
		index->Off();
		AllLevelUpFont_.push_back(index);

		index = Level_->CreateActor<GameEngineContentFont>(12);
		index->SetPosition({ 820, 262 + 60 * 3 });
		index->Off();
		AllLevelUpFont_.push_back(index);

		index = Level_->CreateActor<GameEngineContentFont>(12);
		index->SetPosition({ 820, 262 + 60 * 4 });
		index->Off();
		AllLevelUpFont_.push_back(index);

		index = Level_->CreateActor<GameEngineContentFont>(12);
		index->SetPosition({ 820, 262 + 60 * 5 });
		index->Off();
		AllLevelUpFont_.push_back(index);


		BattleStatus_ = CreateRenderer("BattleStatus.bmp", 11);
		BattleStatus_->SetPivot({ 59 , -108 });
		BattleStatus_->Off();
	}
	// 키 생성
	GameEngineInput::GetInst()->CreateKey("SLeft", VK_LEFT);
	GameEngineInput::GetInst()->CreateKey("SRight", VK_RIGHT);
	GameEngineInput::GetInst()->CreateKey("SDown", VK_DOWN);
	GameEngineInput::GetInst()->CreateKey("SUp", VK_UP);
	GameEngineInput::GetInst()->CreateKey("SSelect", 'Z');
	GameEngineInput::GetInst()->CreateKey("SCancel", 'X');
	GameEngineInput::GetInst()->CreateKey("StartBattlePage", 'H');
	GameEngineInput::GetInst()->CreateKey("PokeBall", VK_ADD);
	//

	InterfaceImage = CreateRenderer("Battle_Select.bmp", 6);
	InterfaceImage->Off();
	Select = CreateRenderer("Select.bmp", 8);
	Select->Off();

	EnemyHPUI = CreateRenderer("EnemyHPBackground4.bmp", 2);
	EnemyHPUI->Off();
	EnemyHP = CreateRenderer("EnemyHPBar4.bmp", 3, RenderPivot::LeftTop);
	EnemyHP->Off();
	MyHPUI = CreateRenderer("FriendlyHPBackground4.bmp", 2);
	MyHPUI->Off();
	MyHP = CreateRenderer("FriendlyHPBar4.bmp", 3, RenderPivot::LeftTop);
	MyHP->Off();
	EXP = CreateRenderer("FriendlyHPExp4.bmp", 99,RenderPivot::LeftTop);
	EXP->Off();
	BattleCommend = CreateRenderer("BattleCommend4.bmp", 7);
	//Player = CreateRenderer("Player.bmp",0);

	//=========랜더러 위치 설정==========//
	Select->SetPivot({ -190.0f, -25.0f });

	MyHPUI->SetPivot({ 0.0f,-170.0f });
	EnemyHPUI->SetPivot({ -450.0f,-430.0f });
	EnemyHP->SetPivot({ -502.0f,-436.0f });
	MyHP->SetPivot({ -16.0f, -180.0f });
	EXP->SetPivot({ -80.0f,-256.0f });
	BattleCommend->SetPivot({ -240.0f,0.0f });
	BattleCommend->Off();//배틀커맨드는 Fight상태일때만

	//동원씨 도움 RegistActor=이미 만들어진 Actor를 Level에 등록
	GetLevel()->RegistActor("BattleInterface", this);
	//김예나:테스트 코드
	BattleUnit = dynamic_cast<BattleUnitRenderer*>(Level_->FindActor("BattleUnitRenderer"));
	Fonts = Level_->CreateActor<GameEngineContentFont>(8);
	Fonts->SetPosition({ 50, 485 });

	PPFont_ = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 50);
	MaxPPFont_ = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 50);
	TypeFont_ = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 50);


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
	}



	if (BattleUnit->GetPlayerStop() == true && OneTalk == false)
	{
		//김예나:플레이어 멈출시 폰트출력 테스트
		//Fonts->ShowString("Wild NAME\\is appear!!\\Go!!\\NAME!!", false);
		if (Level_->GetBattleData()->IsWild())
		{
			StartWildTalk();
		}
		else
		{
			StartNPCTalk();
		}
	
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
		ShowSkillInfo(0);
		Select->SetPivot({ -680.0f,-30.0f });
		break;
	case 1:
		ShowSkillInfo(1);
		Select->SetPivot({ -380.0f,-30.0f });
		break;
	case 2:
		ShowSkillInfo(2);
		Select->SetPivot({ -680.0f,35.0f });
		break;
	case 3:
		ShowSkillInfo(3);
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

			Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetSkill()[SkillUIPos_]->GetInfo()->GetPP()--;
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

		PPFont_->Off();
		MaxPPFont_->Off();
		TypeFont_->Off();

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

	PPFont_->Off();
	MaxPPFont_->Off();
	TypeFont_->Off();
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
	BattleFont_->ShowString("It's Super\\effective!");
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
void BattleInterface::ShowChangePokemon(const std::string& _Poe, const std::string& _PoePokemon)
{
	BattleFont_->EndFont();
	BattleFont_->ShowString(_Poe + " sent\\out " + _PoePokemon + "!");
	Level_->EndFont_ = false;
}
void BattleInterface::ShowLevelUp(const std::string& _PlayerPokemon, int _Lv, bool _Idx)
{
	BattleFont_->EndFont();
	BattleFont_->ShowString(_PlayerPokemon + "grew to\\LV. " + std::to_string(_Lv) + "!", _Idx);
	Level_->EndFont_ = false;
}

void BattleInterface::ShowRunaway()
{
	BattleFont_->EndFont();
	BattleFont_->ShowString("Got away safely!");
	Level_->EndFont_ = false;
}

void BattleInterface::ShowUsePokeball()
{
	BattleFont_->EndFont();
	BattleFont_->ShowString("Red used\\POKe BALL!");
	Level_->EndFont_ = false;
}
void BattleInterface::ShowGotPokemonByBall(const std::string& _WildPokemon)
{
	BattleFont_->EndFont();
	BattleFont_->ShowString("Gotcha!\\" + _WildPokemon + " was caught!");
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
		if (GameEngineInput::GetInst()->IsDown("PokeBall"))
		{
			BattleUnit->SetFighting(true);
			InterfaceImage->Off();
			BattleCommend->Off();
			Select->Off();
			dynamic_cast<Bag*>(ChildUI_)->DestroyBag();
			ChildUI_->Off();
			Level_->StartBattlePage();
		}
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
	if ((Select->GetPivot().x == 30.0f && Select->GetPivot().y == 35.0f) && true == GameEngineInput::GetInst()->IsDown("SSelect"))
	{
		BattleUnit->SetFighting(true);
		CurOrder = BattleOrder::Run;
		InterfaceImage->Off();
		BattleCommend->Off();
		Select->Off();
		ShowRunaway();
		Level_->BState_ = BattleState::Endding;
		
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
		EXP->SetPivot({ -80.0f,-260.0f });
		PlayerName_->SetPosition({ 570 ,  312 - 4 });
		PlayerLevel_->SetPosition({ 865 , 312 - 4 });
		PlayerHP_->SetPosition({ 770 , 384 - 4 });

	}

	if ((int)TimeCheck % 2 == 1)
	{
		MyHPUI->SetPivot({ 0.0f,-170.0f });
		MyHP->SetPivot({ -16.0f, -180.0f });
		EXP->SetPivot({ -80.0f,-256.0f });
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
				ChildUI_->SetPosition(float4(0, 0));
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
				ChildUI_->SetPosition(float4(0, 0) + GameEngineWindow::GetScale().Half());
				dynamic_cast<Bag*>(ChildUI_)->SetPlayerItemList(PlayerRed::MainRed_->GetItemList());
				dynamic_cast<Bag*>(ChildUI_)->BagInit();

			}
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

	//HP정보 업데이트
	PrevPlayerHp_ = Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetHp();
	PrevFoeHp_ = Level_->BattleData_->GetCurrentPoePokemon()->GetPokemon()->GetInfo()->GetHp();
	PrevExp_ = Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetExp();

	LerpFoeHp_ = static_cast<float>(PrevFoeHp_);
	LerpPlayerHp_ = static_cast<float>(PrevPlayerHp_);
	LerpExp_ = static_cast<float>(LerpExp_);
	

}

void BattleInterface::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

	Reset();

}

void BattleInterface::StartWildTalk()
{
	Fonts->ClearCurrentFonts();
	Fonts->ShowString("Wild " + Level_->GetBattleData()->GetCurrentPoePokemon()->GetPokemon()->GetInfo()->GetNameConstRef() + "\\is appear!!\\Go!!\\"
		+ Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetNameConstRef() + "!!", false);
}

void BattleInterface::StartNPCTalk()
{
	Fonts->ClearCurrentFonts();
	Fonts->ShowString(Level_->GetBattleData()->GetNameString() + "\\would like to battle!\\Go!\\"
		+ Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetNameConstRef() + "!", false);
}

//김예나 : 6월14일 Test추가 함수
//void BattleInterface::NextNPCTalk()
//{
//	Fonts->ClearCurrentFonts();
//	Fonts->ShowString(Level_->GetBattleData()->GetNameString() + "\\Send\\"
//		+ Level_->GetBattleData()->GetCurrentPoePokemon()->GetPokemon()->GetInfo()->GetNameConstRef() + "!", false);
//}

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
	BattleStatus_->Off();
	for (auto Iter : AllSkillFont_)
	{
		Iter->ClearCurrentFonts();
	}
	for (auto Iter : AllLevelUpFont_)
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


	//PPFont_->Death();
	//MaxPPFont_->Death();
	//TypeFont_->Death();
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

void BattleInterface::ShowSkillInfo(int _Index)
{
	if (Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetSkill().size() <= _Index)
	{
		PPFont_->ClearCurrentFonts();
		PPFont_->ShowString("-", true);

		MaxPPFont_->ClearCurrentFonts();
		MaxPPFont_->ShowString("-", true);

		TypeFont_->ClearCurrentFonts();
		TypeFont_->ShowString("-", true);
		return;
	}

	if (false == PPFont_->IsUpdate())
	{
		PPFont_->On();
		MaxPPFont_->On();
		TypeFont_->On();
	}

	//PP
	PPFont_->SetPosition(GameEngineWindow::GetScale().Half() + float4{ 300, 170 });

	int PPCount = Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetSkill()[_Index]->GetInfo()->GetPP();

	PPFont_->ClearCurrentFonts();
	PPFont_->ShowString(std::to_string(PPCount), true);


	//Max PP
	MaxPPFont_->SetPosition(GameEngineWindow::GetScale().Half() + float4{ 390, 170 });

	int MaxPPCount = Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetSkill()[_Index]->GetInfo()->GetMaxPP();

	MaxPPFont_->ClearCurrentFonts();
	MaxPPFont_->ShowString(std::to_string(MaxPPCount), true);


	//타입 
	TypeFont_->SetPosition(GameEngineWindow::GetScale().Half() + float4{ 290, 235 });

	int TypeCount = (int)Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetSkill()[_Index]->GetInfo()->GetType();

	Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetSkill();

	switch (TypeCount)
	{
	case 0:
		TypeFont_->ClearCurrentFonts();
		TypeFont_->ShowString("NORMAL", true);
		break;
	case 2:
		TypeFont_->ClearCurrentFonts();
		TypeFont_->ShowString("WATER", true);
		break;
	default:
		TypeFont_->ClearCurrentFonts();
		TypeFont_->ShowString("NORMAL", true);
		break;
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

		//HP폰트 업데이트
		PlayerHP_->EndFont();
		PlayerHP_ = Level_->CreateActor<GameEngineContentFont>(10);
		PlayerHP_->SetPosition({ 770 , 384 });
		PlayerHP_->SetSize(0.75f);
		PlayerHP_->ShowString(std::to_string(static_cast<int>(LerpPlayerHp_))
			+ "/ " + std::to_string(Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetMaxHp()), true);

		//보간값이 변화된 적 HP와 같아지면 보간 종료
		if (static_cast<int>(LerpPlayerHp_) == PlayerHP)
		{
			PrevPlayerHp_ = PlayerHP;
			HpRenderTimer_ = 0.0f;
		}
	}

	//경험치의 변화를 감지하고 경험치 보간 진행
	int PlayerExp = Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetExp();
	if (PlayerExp != PrevExp_)
	{
		ExpRenderTimer_ += GameEngineTime::GetDeltaTime();
		LerpExp_ = GameEngineMath::LerpLimit(static_cast<float>(PrevExp_), static_cast<float>(PlayerExp), ExpRenderTimer_);

		//보간값이 변화된 값과 같아지면 보간 종료
		if (static_cast<int>(LerpExp_) == PlayerExp)
		{
			PrevExp_ = PlayerExp;
			ExpRenderTimer_ = 0.0f;
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
	
	//플레이여 경험치 렌더링
	{
		float ExpRatio =  LerpExp_ / static_cast<float>(Level_->BattleData_->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetMaxExp());
		if (ExpRatio >= 1.0f)
		{
			ExpRatio = 1.0f;
		}
		float ExpXScale = GameEngineImageManager::GetInst()->Find("FriendlyHPExp4.bmp")->GetScale().x * ExpRatio;
		EXP->SetScale({ ExpXScale ,EXP->GetScale().y });
	}


}


void BattleInterface::LevelStatu()
{

	std::queue<int> AA;
	BattleStatus_->On();
	int Idx = 0;
	for (auto Iter : AllLevelUpFont_)
	{
		AA.push(0);
		Iter->ClearCurrentFonts();
		Iter->On();
	}
	AA;
	Idx = GameEngineRandom::GetInst_->RandomInt(1, 3);
	AllLevelUpFont_[0]->ShowString("+ " + std::to_string(Idx), true);
	Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->SetMaxHp(Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetMaxHp() + Idx);
	Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->SetHp(Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetMaxHp());
	Idx = GameEngineRandom::GetInst_->RandomInt(1, 3);
	AllLevelUpFont_[1]->ShowString("+ " + std::to_string(Idx), true);
	Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->SetAtt(Idx);
	Idx = GameEngineRandom::GetInst_->RandomInt(1, 3);
	AllLevelUpFont_[2]->ShowString("+ " + std::to_string(Idx), true);
	Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->SetAtt(Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetAtt() + Idx);
	Idx = GameEngineRandom::GetInst_->RandomInt(1, 3);
	AllLevelUpFont_[3]->ShowString("+ " + std::to_string(Idx), true);
	Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->SetDef(Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetDef() + Idx);
	Idx = GameEngineRandom::GetInst_->RandomInt(1, 3);
	AllLevelUpFont_[4]->ShowString("+ " + std::to_string(Idx), true);
	Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->SetSpAtt(Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetSpAtt() + Idx);
	Idx = GameEngineRandom::GetInst_->RandomInt(1, 3);
	AllLevelUpFont_[5]->ShowString("+ " + std::to_string(Idx), true);
	Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->SetSpDef(Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetSpDef() + Idx);

}