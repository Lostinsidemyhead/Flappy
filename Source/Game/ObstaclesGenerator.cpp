#include "ObstaclesGenerator.h"

ObstaclesGenerator::ObstaclesGenerator(float MinPosY, float MaxPosY, float StartPosX)
{
	TopLimit = static_cast<float>(MinPosY);
	BottomLimit = static_cast<float>(MaxPosY);
	HolePosY = (MaxPosY - MinPosY) / 2;
	PosX = StartPosX;
	ObstacleSize = glm::vec2(ObstacleWidth, MaxPosY - MinPosY);
}

float ObstaclesGenerator::GenerateObstacleHeight()
{
	float Range = BottomLimit - TopLimit;
	std::random_device RD{};
	std::mt19937 Generator{ RD() };
	std::normal_distribution<> Random{ Range / 2,  Range / 4};
	
	HolePosY = Random(Generator);
	
	if (HolePosY < TopLimit + HoleSize)
	{
		HolePosY += HoleSize;
	}

	return HolePosY;
}

Obstacle* ObstaclesGenerator::CreateObstacle()
{
	float ObstacleHeight = GenerateObstacleHeight();
	glm::vec2 ObstaclePos = glm::vec2(PosX, ObstacleHeight);
	std::cout << ObstacleHeight << std::endl;

	return new Obstacle(ObstaclePos, ObstacleSize, ResourceManager::GetTexture("Obstacle"), HoleSize);
}