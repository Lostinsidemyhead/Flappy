#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include "Obstacle.h"
#include <iostream>
#include <random>

const float OBSTACLE_WIDTH = 75.0f;

class ObstaclesGenerator {
public:
	ObstaclesGenerator(float MinPosY, float MaxPosY, float StartPosX);
	float GenerateObstacleHeight();
	Obstacle* CreateObstacle();

private:
	float TopLimit, BottomLimit;
	float HolePosY;
	float HoleSize = 150.0f;
	glm::vec2 ObstacleSize;
	float PosX;
};