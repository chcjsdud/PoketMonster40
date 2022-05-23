#include "Item.h"
#include <GameEngine/GameEngineImageManager.h>

Item::Item() 
	: Value_(0)
	, Type_(ItemType::ITEM)
	, Desc_{}
{
}

Item::~Item() 
{
}

