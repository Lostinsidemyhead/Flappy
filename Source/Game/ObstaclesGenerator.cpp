#include "ObstaclesGenerator.h"

ObstaclesGenerator::ObstaclesGenerator(int Min, int Max)
{
	TopLimit = static_cast<float>(Min);
	BottomLimit = static_cast<float>(Max);
}

float ObstaclesGenerator::GenerateObstacle()
{
	float Range = BottomLimit - TopLimit;
	std::random_device RD{};
	std::mt19937 Generator{ RD() };
	std::normal_distribution<> Random{ Range / 2,  Range / 4};
	
	HoleHeight = Random(Generator);
	
	if (HoleHeight < TopLimit + HoleSize)
	{
		HoleHeight += HoleSize;
	}

	return HoleHeight;
}