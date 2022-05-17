#include "TitleBackground.h"


TitleBackground::TitleBackground()
{

}

TitleBackground::~TitleBackground()
{

}

void TitleBackground::Start()
{
	CreateRenderer("TestTitle.bmp");
	SetPosition({ 480.0f, 320.0f });//반반 위치에(정 가운데에) 셋팅
}

