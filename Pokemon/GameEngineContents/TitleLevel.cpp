#include "TitleLevel.h"
#include "TitleBackground.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackground>();
}

void TitleLevel::Update()
{
}