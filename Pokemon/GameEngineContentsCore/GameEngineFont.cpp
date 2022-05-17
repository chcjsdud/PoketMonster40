#include "GameEngineFont.h"

GameEngineFont::GameEngineFont() 
	: WaitTime_(0.02f)
	, FirstCharPos_(float4::ZERO)
{
}

GameEngineFont::~GameEngineFont() 
{

}

void GameEngineFont::Start()
{
	GameEngineFont::AllFonts_.push_back(this);
}

void GameEngineFont::Update()
{

}



void GameEngineFont::Destroy()
{
	for (auto Font : AllFonts_)
	{
		if (Font != nullptr)
		{
			delete Font;
			Font = nullptr;
		}
	}
}