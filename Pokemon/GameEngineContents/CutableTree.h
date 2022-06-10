#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class CutableTree : public GameEngineActor
{
public:
	// constrcuter destructer
	CutableTree();
	~CutableTree();

	// delete Function
	CutableTree(const CutableTree& _Other) = delete;
	CutableTree(CutableTree&& _Other) noexcept = delete;
	CutableTree& operator=(const CutableTree& _Other) = delete;
	CutableTree& operator=(CutableTree&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* Renderer_;

	void Start() override;
};

