#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include "Obstacle.h"
#include <iostream>
#include <random>

class ObstaclesGenerator {
public:
	ObstaclesGenerator(int Min, int Max);
	float GetHoleSize() { return HoleSize; }
	float GenerateObstacle();

private:
	float TopLimit;
	float BottomLimit;
	float HoleHeight;
	float HoleSize = 150.0f;
};