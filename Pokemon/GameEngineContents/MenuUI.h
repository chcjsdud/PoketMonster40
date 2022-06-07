#pragma once
#include <GameEngine/GameEngineActor.h>

class FadeActor;
class PokemonInfo;
class GameEngineContentFont;
class MenuUI : public GameEngineActor
{
public:
	MenuUI();
	~MenuUI();


	MenuUI(const MenuUI& _Other) = delete;
	MenuUI(const MenuUI&& _Other) noexcept = delete;
	MenuUI& operator=(const MenuUI& _Ohter) = delete;
	MenuUI& operator=(const MenuUI&& _Other) noexcept = delete;

	void InitMenuUI();

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	bool IsOn_; // 이게 true가 되야 액터가 업데이트

	int CurrentOrder_;
	std::vector<GameEngineRenderer*> MenuUIRenderer_;
	FadeActor* FadeActor_;
	GameEngineActor* ChildUI_;

};

