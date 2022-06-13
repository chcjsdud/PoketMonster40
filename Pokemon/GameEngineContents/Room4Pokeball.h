#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Room4Pokeball : public GameEngineActor
{
public:
	// constrcuter destructer
	Room4Pokeball();
	~Room4Pokeball();

	// delete Function
	Room4Pokeball(const Room4Pokeball& _Other) = delete;
	Room4Pokeball(Room4Pokeball&& _Other) noexcept = delete;
	Room4Pokeball& operator=(const Room4Pokeball& _Other) = delete;
	Room4Pokeball& operator=(Room4Pokeball&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* Renderer_;

	void Start() override;
};

