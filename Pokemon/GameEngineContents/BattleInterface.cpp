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
	, EmptyString_(false)
	, BattleFont_(nullptr)
	, SkillUIPos_(0)
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
	// 키 생성
	GameEngineInput::GetInst()->CreateKey("SLeft", VK_LEFT);
	GameEngineInput::GetInst()->CreateKey("SRight", VK_RIGHT);
	GameEngineInput::GetInst()->CreateKey("SDown", VK_DOWN);
	GameEngineInput::GetInst()->CreateKey("SUp", VK_UP);
	GameEngineInput::GetInst()->CreateKey("SSelect", 'Z');
	GameEngineInput::GetInst()->CreateKey("SCancel", 'X');
	GameEngineInput::GetInst()->CreateKey("StartBattlePage", 'H');
	//

	InterfaceImage = CreateRenderer("Battle_Select.bmp", 5);
	InterfaceImage->Off();
	Select = CreateRenderer("Select.bmp", 7);
	Select->Off();

	EnemyHPUI = CreateRenderer("EnemyHPBackground4.bmp", 2);
	EnemyHPUI->Off();
	EnemyHP = CreateRenderer("EnemyHPBar4.bmp", 3);
	EnemyHP->Off();
	MyHPUI = CreateRenderer("FriendlyHPBackground4.bmp", 2);
	MyHPUI->Off();
	MyHP = CreateRenderer("FriendlyHPBar4.bmp", 3);
	MyHP->Off();
	EXP = CreateRenderer("FriendlyHPExp4.bmp", 3);
	EXP->Off();
	BattleCommend = CreateRenderer("BattleCommend4.bmp", 6);
	//Player = CreateRenderer("Player.bmp",0);

	//=========랜더러 위치 설정==========//
	Select->SetPivot({ -190.0f, -25.0f });

	MyHPUI->SetPivot({ 0.0f,-170.0f });
	EnemyHPUI->SetPivot({ -450.0f,-430.0f });
	EnemyHP->SetPivot({ -406.0f,-430.0f });
	MyHP->SetPivot({ 80.0f, -170.0f });
	EXP->SetPivot({ 48.0f,-170.0f });
	BattleCommend->SetPivot({ -240.0f,0.0f });
	BattleCommend->Off();//배틀커맨드는 Fight상태일때만

	//동원씨 도움 RegistActor=이미 만들어진 Actor를 Level에 등록
	GetLevel()->RegistActor("BattleInterface", this);
	//김예나:테스트 코드
	BattleUnit = Level_->CreateActor<BattleUnitRenderer>();
	Fonts = Level_->CreateActor<GameEngineContentFont>(8);
	Fonts->SetPosition({ 50, 485 });

}

void BattleInterface::Render()
{
}

void BattleInterface::Update()
{

	TimeCheck += (GameEngineTime::GetDeltaTime() * 2.0f);
	if (Level_->GetBattleState() != BattleState::BattlePage)
	{
		SelectOrder();
		OrderCheck();
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
			if (Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetSkill().size() == 0)
			{
				MsgBoxAssert("스킬이 없습니다")
			}
			Level_->StartBattlePage(Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetSkill()[SkillUIPos_]->GetInfo()
				, RandomPoeSkill(Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()));
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
		return _Pokemon->GetInfo()->GetSkill()[GameEngineRandom::GetRandom()->RandomInt(0, (size_t)(_Pokemon->GetInfo()->GetSkill().size() - 1))]->GetInfo();
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
	if (EmptyString_ == false)
	{
		if (GameEngineInput::GetInst()->IsDown("SSelect"))
		{
			if (BattleFont_->IsEnd())
			{
				BattleFont_->EndFont();
				return true;
			}
			//else
			//{
			//	Fonts->SkipCharAnimation();
			//	return false;
			//}
		}
	}
	else
	{
		EmptyString_ = false;
		return true;
	}
	return false;
}

void BattleInterface::ShowUsedSkillString(const std::string& _AttPokemon, const std::string& _AttSkill)
{
	BattleFont_->EndFont();
	BattleFont_->ShowString(_AttPokemon + " Used\\" + _AttSkill + "!");
}

void BattleInterface::ShowPoeFaintString(const std::string& _PoePokemon)
{
	BattleFont_->EndFont();
	BattleFont_->ShowString("Poe " + _PoePokemon + "\\fainted!");
}

void BattleInterface::ShowSupperEffectString()
{
	BattleFont_->EndFont();
	BattleFont_->ShowString("It's Supe\\effective!");
}

void BattleInterface::ShowCriticalHitString()
{
	BattleFont_->EndFont();
	BattleFont_->ShowString("A critical hit!");
}

void BattleInterface::ShowNotEffective()
{
	BattleFont_->EndFont();
	BattleFont_->ShowString("It's not Very\\effective;");
}

void BattleInterface::ShowFailed()
{
	BattleFont_->EndFont();
	BattleFont_->ShowString("But it failed!");
}

void BattleInterface::ShowRankUpAndDown(const std::string& _Pokemon, PokemonAbility _Ability, int _Rank)
{
	BattleFont_->EndFont();
	std::string Rankfont = _Pokemon;
	Rankfont += " is\\";
	Rankfont += AbilityString(_Ability);
	Rankfont += RankString(_Rank);
	BattleFont_->ShowString(Rankfont);
}

std::string BattleInterface::AbilityString(PokemonAbility _Ability)
{
	switch (_Ability)
	{
	case PokemonAbility::Att:
		return "ATTACK";
		break;
	case PokemonAbility::Def:
		return "DEFENSE";
		break;
	case PokemonAbility::SpAtt:
		return "SPECIAL ATTACK";
		break;
	case PokemonAbility::SpDef:
		return "SPECIAL DEFENSE";
		break;
	case PokemonAbility::Speed:
		return "SPEED";
		break;
	case PokemonAbility::Accuracy:
		return "ACCURACY";
		break;
	case PokemonAbility::Evasion:
		return "EVASION";
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
	if (InterfaceImage->IsUpdate() == true)
	{
		switch (CurOrder)
		{
		case BattleOrder::Fight:
			break;
		case BattleOrder::Bag:
			break;
		case BattleOrder::Pokemon:
			break;
		case BattleOrder::Run:
			break;
		case BattleOrder::None:
			break;
		default:
			break;
		}
		if (CurOrder == BattleOrder::None)
		{
			
		}
		

	}

	if (CurOrder == BattleOrder::Fight)
	{
		ShowPokemonSkill(Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon());
		ShowAndCheckSkillPos();
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
		MyHP->SetPivot({ 80.0f, -174.0f });
		EXP->SetPivot({ 48.0f,-174.0f });
	}

	if ((int)TimeCheck % 2 == 1)
	{
		MyHPUI->SetPivot({ 0.0f,-170.0f });
		MyHP->SetPivot({ 80.0f, -170.0f });
		EXP->SetPivot({ 48.0f,-170.0f });
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
	if (InterfaceImage->IsUpdate() == true)
	{
		if ((Select->GetPivot().x == -190.0f && Select->GetPivot().y == -25.0f) && true == GameEngineInput::GetInst()->IsDown("SSelect"))
		{	//싸우다 선택
			CurOrder = BattleOrder::Fight;
		}

		if ((Select->GetPivot().x == -190.0f && Select->GetPivot().y == 35.0f) && true == GameEngineInput::GetInst()->IsDown("SSelect"))
		{	//포켓몬 선택
			CurOrder = BattleOrder::Pokemon;
		}

		if ((Select->GetPivot().x == 30.0f && Select->GetPivot().y == -25.0f) && true == GameEngineInput::GetInst()->IsDown("SSelect"))
		{	//가방 선택
			CurOrder = BattleOrder::Bag;
		}

		if ((Select->GetPivot().x == 30.0f && Select->GetPivot().y == 35.0f) && true == GameEngineInput::GetInst()->IsDown("SSelect"))
		{
			CurOrder = BattleOrder::Run;
		}

		//if (CurOrder == BattleOrder::Fight && true == GameEngineInput::GetInst()->IsDown("SCancel"))
		//{
		//	BattleCommend->Off();
		//	Select->SetPivot({ -190.0f,-25.0f });
		//	CurOrder = BattleOrder::None;
		//}
	}
}

void BattleInterface::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	OneTalk = false;
}

void BattleInterface::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

	Reset();

}

void BattleInterface::StartTalk()
{
	const std::string& Name = Level_->GetBattleData()->GetCurrentPlayerPokemon()->GetPokemon()->GetInfo()->GetNameConstRef();
	Fonts->ShowString("Wild " + Name + "\\is appear!!\\Go!!\\" + Name + "!!", false);
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

	// 스킬 마우스포인터
	SkillUIPos_ = 0;
}