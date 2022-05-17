#pragma once
#include <GameEngine/GameEngine.h>

// 설명 : 선생님은 만들려는 게임이 없으니까 그냥 스터디게임이라도 지었습니다.
//       여러분들은 각자 자신이 만들려는 게임에 맞는 이름을 이녀석에게 붙여주시면 됩니다.
class PokemonEngine : public GameEngine
{
public:
	// constrcuter destructer
	PokemonEngine();
	~PokemonEngine();

	// delete Function
	PokemonEngine(const PokemonEngine& _Other) = delete;
	PokemonEngine(PokemonEngine&& _Other) noexcept = delete;
	PokemonEngine& operator=(const PokemonEngine& _Other) = delete;
	PokemonEngine& operator=(PokemonEngine&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;

	void InitUI();
	void InitKey();

protected:

private:

};

