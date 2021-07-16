#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include "Obstacle.h"
#include <iostream>
#include <random>

class ObstaclesGenerator {
public:
	const float ObstacleWidth = 75.0f;
	const float HoleSize =  250.0f; //150

	ObstaclesGenerator(float MinPosY, float MaxPosY, float StartPosX);
	float GenerateObstacleHeight();
	Obstacle* CreateObstacle();

private:
	float TopLimit, BottomLimit;
	float HolePosY;
	glm::vec2 ObstacleSize;
	float PosX;
};