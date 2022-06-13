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
	void ClearText();
	void Setting();
	void ChoiceEnd();

	static bool IsCenterMove_;
	static bool IsCenterAnim_;
	bool ZIgnore_;

protected:

private:
	std::vector<std::string> TextVector_;
	GameEngineRenderer* UIRenderer_;
	GameEngineRenderer* ArrowRenderer_;
	class GameEngineContentFont* Fonts;
	bool IsSetting_;
	bool IsShop_;
	bool IsCenter_;
	bool IsChoice_;
	bool IsBrock_;
	bool IsNPC5Start_;

	void Start() override;
	void Update() override;
	void MakeChoiceOption();
	void WaitingMoveAnim();
};

