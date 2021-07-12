#include "Game.h"




Game::Game(unsigned int Width, unsigned int Height)
	: State(WaitingToStart), Width(Width), Height(Height)
{

}

Game::~Game()
{
	delete Sprite;
	delete Player;
}

void Game::Initialize() 
{
	ResourceManager::LoadShader("../Resources/Shaders/Vertex.txt", "../Resources/Shaders/Fragment.txt", nullptr, "Sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("Sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("Sprite").SetMatrix4("projection", projection);
	
	Sprite = new SpriteRenderer(ResourceManager::GetShader("Sprite"));

	ResourceManager::LoadTexture("../Resources/Textures/Jellyfish.png", true, "Player");
	glm::vec2 PlayerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,this->Height - PLAYER_SIZE.y);
	Player = new Actor(PlayerPos, PLAYER_SIZE, ResourceManager::GetTexture("Player"));
}

void Game::Tick(float DeltaTime)
{

}

void Game::ProcessInput(float DeltaTime)
{

}

void Game::Render() 
{

	Player->Draw(*Sprite);
}