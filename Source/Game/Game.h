#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Actor.h"
#include "../Utils/ResourceManager.h"
#include "../Utils/SpriteRenderer.h"

enum GameState : int{
	WaitingToStart = 0,
	InProgress,
	GAmeOver
}; 

const glm::vec2 PLAYER_SIZE(50.0f, 50.0f);

class Game {
public:
	GameState State;
	unsigned int Width, Height;
	Actor *Player;
	SpriteRenderer *Sprite;

	Game(unsigned int Width, unsigned int Height);
	~Game();

	void Initialize();
	void Tick(float DeltaTime);
	void ProcessInput(float DeltaTime);
	void Render();
};
#endif