#include "Item.h"
#include <GameEngine/GameEngineImageManager.h>

Item::Item() 
	: Value_(0)
{
}

Item::~Item() 
{
}

void Item::SetItemImage(const std::string& _Name)
{
	std::string MyName = _Name + ".bmp";
	MyIcon_ = GameEngineImageManager::GetInst()->Find(MyName);
}
