#include "Game.h"

Game::Game(unsigned int Width, unsigned int Height) 
	: State(WaitingToStart), Width(Width), Height(Height) 
{

}

Game::~Game()
{

}

void Game::Initialize() {}
void Game::Tick() {}
void Game::ProcessInput() {}
void Game::Render() {}