#include "InteractionText.h"
#include <GameEngineContentsCore/GameEngineContentFont.h>
#include <GameEngineBase/GameEngineInput.h>
#include "ContentEnum.h"
#include "PlayerRed.h"
#include "NPCBase.h"
#include "NPC6.h"
#include "Oak.h"
#include "Green.h"
#include "ShopChoiceOption.h"
#include "CenterChoiceOption.h"
#include "YesOrNo.h"
#include "WorldMapLevel.h"
#include "BattleStartUI.h"

bool InteractionText::IsCenterMove_ = false;
bool InteractionText::IsCenterAnim_ = false;
InteractionText::InteractionText() 
	: UIRenderer_(nullptr)
	, Fonts(nullptr)
	, IsSetting_(false)
	, IsShop_(false)
	, IsCenter_(false)
	, IsYesNo_(false)
	, IsChoice_(false)
	, IsBrock_(false)
	, IsShopStart_(false)
	, ZIgnore_(false)
{
}

InteractionText::~InteractionText() 
{
}

void InteractionText::AddText(const std::string& _Text)
{
	TextVector_.push_back(_Text);
}

void InteractionText::Setting()
{
	UIRenderer_ = CreateRenderer("Npc_TextFrame.bmp", static_cast<int>(RenderOrder::UI));
	UIRenderer_->SetPivot({ 0, 225 });

	std::string TmpString = "";
	for (int i = 0; i < TextVector_.size(); i++)
	{
		TmpString += TextVector_[i].c_str();
		TmpString += "\\";
	}
	Fonts = GetLevel()->CreateActor<GameEngineContentFont>(static_cast<int>(RenderOrder::UI));
	Fonts->SetPosition(GetPosition() + float4(-420, 160));
	Fonts->ShowString(TmpString, false);
	IsSetting_ = true;	
}

void InteractionText::ClearText()
{
	TextVector_.clear();
	Fonts->ClearCurrentFonts();
}

void InteractionText::ChoiceEnd()
{
	IsChoice_ = false;
	IsCenter_ = false;
	IsShop_ = false;
	IsYesNo_ = false;

	if (Fonts->IsWait())
	{
		Fonts->NextString();
	}
	if (Fonts->IsEnd())
	{
		PlayerRed::MainRed_->SetInteraction(false);
		Fonts->EndFont();
		NPC6::Text_ = nullptr;
		Death();
	}
}

void InteractionText::Start()
{
	
}

void InteractionText::Update()
{
	SetPosition(PlayerRed::MainRed_->GetPosition());
	Fonts->SetPosition(GetPosition() + float4(-420, 160));

	if (false == IsSetting_ || true == IsChoice_)
	{
		return;
	}
	
	std::string TmpString = Fonts->GetCurrentString();
	if (Fonts->GetCurrentString() == "May I help you?")
	{
		IsShop_ = true;
	}
	else if (Fonts->GetCurrentString() == "Is there anything else I can do?")
	{
		IsShop_ = true;
	}
	else if (Fonts->GetCurrentString() == "perfect health?")
	{
		IsCenter_ = true;
	}
	else if (Fonts->GetCurrentString() == "few seconds.")
	{
		IsCenterMove_ = true;
	}
	else if (Fonts->GetCurrentString() == "full health.")
	{
		IsCenterAnim_ = true;
		ZIgnore_ = true;
	}
	else if (Fonts->GetCurrentString() == "Show me your best!")
	{
		IsBrock_ = true;
	}
	else if (Fonts->GetCurrentString() == "the GRASS POKEMON BULBASAUR?" 
		|| Fonts->GetCurrentString() == "WATER POKEMON SQUIRTLE?"
		|| Fonts->GetCurrentString() == "FIRE POKEMON CHARMANDER?")
	{
		IsYesNo_ = true;
	}
	else if (Fonts->GetCurrentString() == "You came from PALLET TOWN?")
	{
		IsShopStart_ = true;
	}
	else if (true == PlayerRed::MainRed_->GetClearShopEvent() && Fonts->GetCurrentString() == "GREEN: Gramps!")
	{
		IsShopGreen_ = true;
	}

	// 폰트 출력이 완료되고 키입력 대기
	if (Fonts->IsWait())
	{
		MakeChoiceOption();

		// Z 키 입력시 다음 문장 출력
		if (GameEngineInput::GetInst()->IsDown("Z") == true)
		{
			Fonts->NextString();
			IsCenterMove_ = false;
			//IsCenterAnim_ = false;
		}
	}
	// 다음 문장이 없을 때 == 끝났을 때
	if (Fonts->IsEnd())
	{
		MakeChoiceOption();
		WaitingMoveAnim();

		if (true == ZIgnore_)
		{
			return;
		}

		// 대화가 끝났을 때 z 키누르면 종료
		if (GameEngineInput::GetInst()->IsDown("Z") == true)
		{
			if (true == PlayerRed::MainRed_->GetStartEvent())
			{
				PlayerRed::MainRed_->SetOakCall(true);
			}

			if (true == NPCBase::NPC_->GetRedCathEnd())
			{
				NPCBase::NPC_->SetOakFollow(true);
			}

			if (true == NPCBase::NPC_->GetRoom4Enter())
			{
				//NPCBase::NPC_->SetOakFollow(false);
			}

			if (true == Green::NPCGreen->GetSelectDialog())
			{
				Green::NPCGreen->SetRedSelectFinish(true);
			}
			
			if (true == PlayerRed::MainRed_->GetGreenBattle())
			{
				Green::NPCGreen->SetGreenMove(true);
			}
			PlayerRed::MainRed_->SetInteraction(false);
			NPCBase::NPC_->SetNPCInteraction(false);
			IsCenterMove_ = false;
			IsCenterAnim_ = false;
			Fonts->EndFont();
			NPC6::Text_ = nullptr;
			Death();

			if (true == IsBrock_)
			{
				BattleStartUI* TmpBattleStartUI = GetLevel()->CreateActor<BattleStartUI>();
				TmpBattleStartUI->ChangeToBattleLevel(BattleNpcType::Brock);
			}
			if (true == PlayerRed::MainRed_->GetStartShopEvent() && true == IsShopStart_)
			{
				IsShopStart_ = false;
				PlayerRed::MainRed_->RedMoveControll(RedDir::Up, 4);
			}
			if (true == IsShopGreen_)
			{
				IsShopGreen_ = false;
				PlayerRed::MainRed_->SetStartShopOakEvent(true);
			}
		}
	}
}

void InteractionText::MakeChoiceOption()
{
	if (true == IsCenter_)
	{
		CenterChoiceOption* TmpOption = GetLevel()->CreateActor<CenterChoiceOption>();
		TmpOption->SetPosition(GetPosition());
		TmpOption->SetParent(this);
		IsChoice_ = true;
		return;
	}
	if (true == IsShop_)
	{
		ShopChoiceOption* TmpOption = GetLevel()->CreateActor<ShopChoiceOption>();
		TmpOption->SetPosition(GetPosition());
		TmpOption->SetParent(this);
		IsChoice_ = true;
		return;
	}
	if (true == IsYesNo_)
	{
		YesOrNo* TmpOption = GetLevel()->CreateActor<YesOrNo>();
		TmpOption->SetPosition(GetPosition());
		TmpOption->SetParent(this);
		IsChoice_ = true;
		return;
	}
}

void InteractionText::WaitingMoveAnim()
{
	if (true == NPC6::InteractionMove_ || true == NPC6::InteractionAnim_)
	{
		return;
	}

	if (true == IsCenterMove_)
	{
		NPC6::InteractionMove_ = true;
	}
	if (true == IsCenterAnim_)
	{
		NPC6::InteractionAnim_ = true;
	}
}
