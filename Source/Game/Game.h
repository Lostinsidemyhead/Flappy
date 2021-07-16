#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "../Utils/ResourceManager.h"
#include "../Utils/SpriteRenderer.h"
#include "Player.h"
#include "Obstacle.h"
#include "ObstaclesGenerator.h"
#include "../Utils/TextRenderer.h"
#include <iostream>

enum GameState : int{
	WaitingToStart = 0,
	InProgress,
	GameOver
}; 

const glm::vec2 PLAYER_SIZE(50.0f, 50.0f);
class Player;

class Game {
public:
	Game(unsigned int Width, unsigned int Height);
	~Game();

	const glm::vec2 PlayerSize = glm::vec2(50.0f, 50.0f);

	void Initialize();
	void Tick(float DeltaTime);
	void ProcessInput(int Key);
	void Render();

private:
	unsigned int Width, Height;
	SpriteRenderer* Sprite;
	GameState State;
	std::string PlayerName = "Player";

	float PlayerVelocity = 200.0f;
	Player* CurrentPlayer;
	unsigned int Score;
	
	ObstaclesGenerator* ObstaclesGen;
	std::vector<Obstacle*> Obstacles;
	float ObstacleVelocity = 200.0f;
	float MinDistanceBetweenObstacles = 200.0f;
	float GameSpeedIncrement = 0.005f;

	bool IsHighResult = false;

	TextRenderer* Text;

	void AddObstacle();
	bool DetectCollision(Obstacle* DetectionObstacle);

	void ScoreCounting(Obstacle* DetectionObstacle);
	void ShowHighScores();
	void SaveCurrentScoreIfRequired();
	std::multimap<unsigned int, std::string, std::greater<int>> GetHighScoreList();

	void GameOver();
};