#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum GameState : int{
	WaitingToStart = 0,
	InProgress,
	GAmeOver
};

class Game {
public:
	GameState State;
	unsigned int Width, Height;

	Game(unsigned int Width, unsigned int Height);
	~Game();

	void Initialize();
	void Tick();
	void ProcessInput();
	void Render();
};

#endif