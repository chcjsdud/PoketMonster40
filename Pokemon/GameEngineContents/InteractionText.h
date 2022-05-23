#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>
#include <string>

// Ό³Έν :
class InteractionText : public GameEngineActor
{
public:
	// constrcuter destructer
	InteractionText();
	~InteractionText();

	// delete Function
	InteractionText(const InteractionText& _Other) = delete;
	InteractionText(InteractionText&& _Other) noexcept = delete;
	InteractionText& operator=(const InteractionText& _Other) = delete;
	InteractionText& operator=(InteractionText&& _Other) noexcept = delete;

	void AddText(const std::string& _Text);
	void Setting();

protected:

private:
	std::vector<std::string> TextVector_;
	GameEngineRenderer* UIRenderer_;
	GameEngineRenderer* ArrowRenderer_;
	class GameEngineContentFont* Fonts;

	void Start() override;
	void Update() override;
};

