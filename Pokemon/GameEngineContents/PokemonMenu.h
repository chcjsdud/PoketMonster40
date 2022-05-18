#pragma once
#include <GameEngine/GameEngineActor.h>


class Pokemon;
class PokemonMenu : public GameEngineActor
{
public:
	PokemonMenu();
	~PokemonMenu();


	PokemonMenu(const PokemonMenu& _Other) = delete;
	PokemonMenu(const PokemonMenu&& _Other) noexcept = delete;
	PokemonMenu& operator=(const PokemonMenu& _Ohter) = delete;
	PokemonMenu& operator=(const PokemonMenu&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	void InitRenderer();
	void GetPlayerPokemon();
	void OnUI(); //UI가 켜질경우

	//폰트 
	class GameEngineContentFont* Fonts;

	//렌더러
	GameEngineRenderer* BackgroundRenderer_;
	GameEngineRenderer* BoxRenderer_[6];
	GameEngineRenderer* DialogRenderer_;
	GameEngineRenderer* CancelRenderer_;
	GameEngineRenderer* PokemonRenderer_[6];

	//----------------------------------------- UI 키입력 관련----------------------------------------------------
	//가지고 있는 포켓몬 수
	int PokemonNumber_;
	//현재 키가 가리키고 있는 순서
	int CurrentOrder_;
	//왼쪽 오른쪽 버튼을 눌렀을 때 기억하는 키 내용
	int RememberOrder_;
	//임시 포켓몬 리스트
	std::vector<Pokemon*> PokemonList_;
};

