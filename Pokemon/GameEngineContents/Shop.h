#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentEnum.h"
#include "Item.h"

enum class ShopState
{
	SelectSalesList,
	SelectCount,
	SelectBuy,
};

class GameEngineRenderer;
class Shop : public GameEngineActor
{
public:
	Shop();
	~Shop();

	Shop(const Shop& _Other) = delete;
	Shop(Shop&& _Other) noexcept = delete;
	Shop& operator=(const Shop& _Other) = delete;
	Shop& operator=(Shop&& _Other) noexcept = delete;
	
	void ShopInit();
	void ShopDestroy();

	void OpenSalesList();
	void OpenCountDialog();
	void OpenBuyDialog();

	void DestroyAllFonts();
	void DestroyCountFont();
	void DestroyMoneyFont();
	void DestroyInBagFont();

	void ArrowUpdate();

	inline void SetPlayerItemList(std::vector<Item*>& _List)
	{
		for (int i = 0; i < _List.size(); ++i)
		{
			if (ItemType::ITEM == _List[i]->GetInfo()->GetType())
			{
				ItemList_.push_back(_List[i]);
			}

			else if (ItemType::KEYITEM == _List[i]->GetInfo()->GetType())
			{
				KeyItemList_.push_back(_List[i]);
			}

			else if (ItemType::BALL == _List[i]->GetInfo()->GetType())
			{
				BallList_.push_back(_List[i]);
			}
		}
	}

protected:
	void Start();
	void Update();

private:
	ShopState ShopState_;

	GameEngineRenderer* SalesList_;
	GameEngineRenderer* CountDialog_;
	GameEngineRenderer* InBag_;
	GameEngineRenderer* BuyDialog_;

	GameEngineRenderer* Arrow_;
	GameEngineRenderer* BuyArrow_;
	int ArrowIndex_;
	int BuyArrowIndex_;

	std::vector<Item*> ItemList_;
	std::vector<Item*> KeyItemList_;
	std::vector<Item*> BallList_;

	std::vector<class GameEngineContentFont*> AllFontList_;
	std::vector<class GameEngineContentFont*> CountFontList_; //아이템 구매 개수 폰트
	std::vector<class GameEngineContentFont*> MoneyFontList_;
	std::vector<class GameEngineContentFont*> InBagFontList_;

	GameEngineContentFont* InBagCount_;
	GameEngineContentFont* Money_;
	GameEngineContentFont* PriceFont_;

	int Price_;
	int ItemCount_;

	GameEngineRenderer* ItemPreView_;

	float InputTime_;
};

