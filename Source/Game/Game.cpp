#include "Game.h"

#include <iostream>

Game::Game(unsigned int Width, unsigned int Height)
	: State(InProgress), Width(Width), Height(Height){}

Game::~Game()
{
	delete Sprite;
	delete CurrentPlayer;
}

void Game::Initialize() 
{
	ResourceManager::LoadShader("../Resources/Shaders/Vertex.txt", "../Resources/Shaders/Fragment.txt", nullptr, "Sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Width),
		static_cast<float>(Height), 0.0f, -1.0f, 1.0f);
	
	ResourceManager::GetShader("Sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("Sprite").SetMatrix4("projection", projection);
	
	Sprite = new SpriteRenderer(ResourceManager::GetShader("Sprite"));

	ResourceManager::LoadTexture("../Resources/Textures/Obstacle.png", true, "Obstacle");
	ResourceManager::LoadTexture("../Resources/Textures/Jellyfish.png", true, "Player");
	
	glm::vec2 PlayerPos = glm::vec2(PLAYER_SIZE.x, Height / 2.0f - PLAYER_SIZE.y / 2.0f);

	CurrentPlayer = new Player(PlayerPos, PLAYER_SIZE, ResourceManager::GetTexture("Player"), static_cast<float>(Height) - PLAYER_SIZE.y/2.0f);
}

void Game::Tick(float DeltaTime)
{
	if (State != InProgress) return;
	
	if (CurrentPlayer->GetPosition().y < CurrentPlayer->GetSize().y/2
		|| CurrentPlayer->GetPosition().y > Height - CurrentPlayer->GetSize().y/2)
	{
		GameOver();
	}

	float Distance = Velocity * DeltaTime;
	CurrentPlayer->Move(glm::vec2(0, Distance));

	GenerateObstacle();
}

void Game::GenerateObstacle()
{
	
}

void Game::GameOver()
{
	std::cout << "GAME OVER" << std::endl;
	State = GameState::GameOver;
}

void Game::ProcessInput(int Key)
{
	if (State != InProgress) return;

	if (Key == GLFW_KEY_SPACE)
	{
		CurrentPlayer->Up();
	}
}

void Game::Render() 
{
	if (State != InProgress) return;

	CurrentPlayer->Draw(*Sprite);
	TestObstacle->Draw(*Sprite);
}