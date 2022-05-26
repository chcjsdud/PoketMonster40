#include "ItemInfo.h"
#include <GameEngine/GameEngineImageManager.h>

ItemInfo::ItemInfo() 
	: Value_(0)
	, Type_(ItemType::ITEM)
	, Desc_{}
{
}

ItemInfo::~ItemInfo() 
{
}

