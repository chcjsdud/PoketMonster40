#pragma once
#include <GameEngine/GameEngineActor.h>

enum class ShopState
{
	SelectDialog,
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

	void OpenDialog();
	void OpenSalesList();
	void OpenCountDialog();
	void OpenBuyDialog();

protected:
	void Start();
	void Update();

private:
	ShopState ShopState_;

	GameEngineRenderer* SalesList_;
	GameEngineRenderer* ShopDialog_;
	GameEngineRenderer* CountDialog_;
	GameEngineRenderer* InBag_;
	GameEngineRenderer* BuyDialog_;

	GameEngineRenderer* Arrow_;
};

