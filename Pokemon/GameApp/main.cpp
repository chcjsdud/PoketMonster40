#include <Windows.h>
#include <GameEngineContents/PokemonEngine.h>

int __stdcall WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ char*    lpCmdLine,
    _In_ int       nCmdShow)
{
    GameEngine::Start<PokemonEngine>();
}