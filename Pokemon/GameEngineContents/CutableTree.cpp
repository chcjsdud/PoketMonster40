#include "CutableTree.h"
#include "ContentEnum.h"

CutableTree::CutableTree()
	: Renderer_(nullptr)
{
}

CutableTree::~CutableTree() 
{
}

void CutableTree::Start()
{
	Renderer_ = CreateRenderer("CutableTree.bmp", static_cast<int>(RenderOrder::Player));
}

