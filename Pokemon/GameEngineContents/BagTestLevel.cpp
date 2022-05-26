#include "BagTestLevel.h"
#include "Bag.h"
#include "GameEngineBase/GameEngineInput.h"
#include "TestActor.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngineBase/GameEngineWindow.h"

BagTestLevel::BagTestLevel() 
{
}

BagTestLevel::~BagTestLevel() 
{
}

void BagTestLevel::Loading()
{
	//_CrtSetBreakAlloc(276692);
	//_CrtSetBreakAlloc(276479);
	//_CrtSetBreakAlloc(276474);
	//_CrtSetBreakAlloc(276469);
	//_CrtSetBreakAlloc(276464);
	//_CrtSetBreakAlloc(258444);
	//_CrtSetBreakAlloc(162742);

	Bag_ = CreateActor<Bag>();
	Bag_->BagInit();

	TestActor* Actor = CreateActor<TestActor>();
	GameEngineRenderer* Renderer = Actor->CreateRenderer("WorldMaps.bmp");
	Renderer->SetPivot({ GameEngineWindow ::GetScale().Half()});

	if (false == GameEngineInput::GetInst()->IsKey("Close"))
	{
		GameEngineInput::GetInst()->CreateKey("Close", VK_ESCAPE);
		GameEngineInput::GetInst()->CreateKey("On", 'S');
	}
}

void BagTestLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Close")
		&& Bag_ != nullptr)
	{
		Bag_->DestroyBag();
		Bag_->Death();
		Bag_ = nullptr;
	}

	else if(true == GameEngineInput::GetInst()->IsDown("On")
		&& Bag_ == nullptr)
	{
		Bag_ = CreateActor<Bag>();
		Bag_->BagInit();
	}

}

void BagTestLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{


}

void BagTestLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{

}

