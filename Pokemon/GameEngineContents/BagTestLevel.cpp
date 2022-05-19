#include "BagTestLevel.h"
#include "Bag.h"

BagTestLevel::BagTestLevel() 
{
}

BagTestLevel::~BagTestLevel() 
{
}

void BagTestLevel::Loading()
{
	Bag_ = CreateActor<Bag>();
}

void BagTestLevel::Update()
{
}

