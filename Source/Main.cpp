#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Game/Game.h"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

void glfwKeyCallback(GLFWwindow* Window, int Key, int ScannedCode, int Action, int Mode);
void glfwCharCallback(GLFWwindow* Window, unsigned int CodePoint);

Game Flappy(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char* argv[])
{
	if (!glfwInit())
	{
		std::cout << "INIT GLFW FAILED!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);

	GLFWwindow* Window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy", nullptr, nullptr);
	glfwMakeContextCurrent(Window);

	if (!Window)
	{
		std::cout << "WINDOW CREATE FAILED!" << std::endl;
		glfwTerminate();
		return -1;
	}

	if (!gladLoadGL())
	{
		std::cout << "GLAD LOAD FAILED!" << std::endl;
		return -1;
	}

	glfwSetKeyCallback(Window, glfwKeyCallback);
	glfwSetCharCallback(Window, glfwCharCallback);

	// Конфигурация OpenGL
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Flappy.Initialize();

	float DeltaTime = 0.0f;
	float LastFrameTime = 0.0f;

	while (!glfwWindowShouldClose(Window))
	{
		float CurrentFrameTime = glfwGetTime();
		DeltaTime = CurrentFrameTime - LastFrameTime;
		LastFrameTime = CurrentFrameTime;

		glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Flappy.Tick(DeltaTime);
		Flappy.Render();

		glfwSwapBuffers(Window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void glfwKeyCallback(GLFWwindow* Window, int Key, int ScannedCode, int Action, int Mode)
{
	if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS && Flappy.GetGameState() == GameState::WaitingToStart)
	{
		glfwSetWindowShouldClose(Window, GL_TRUE);
	}
	else
	{
		Flappy.ProcessInput(Key, Action);
	}
}
void glfwCharCallback(GLFWwindow* Window, unsigned int CodePoint)
{}