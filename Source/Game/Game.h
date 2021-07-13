#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "../Utils/ResourceManager.h"
#include "../Utils/SpriteRenderer.h"
#include "Player.h"
#include "Obstacle.h"

enum GameState : int{
	WaitingToStart = 0,
	InProgress,
	GameOver
}; 

const glm::vec2 PLAYER_SIZE(50.0f, 50.0f);
const glm::vec2 OBSTACLE_SIZE(100.f, 800.0f);

class Player;

class Game {
public:
	Game(unsigned int Width, unsigned int Height);
	~Game();

	void Initialize();
	void Tick(float DeltaTime);
	void ProcessInput(int Key);
	void Render();

private:
	unsigned int Width, Height;
	GameState State;
	SpriteRenderer* Sprite;

	float Velocity = 200.0f;
	Player* CurrentPlayer;
	Obstacle* TestObstacle;

	void GenerateObstacle();
	void GameOver();
};