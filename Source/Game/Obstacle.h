#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Actor.h"
#include "../Utils/ResourceManager.h"
#include "../Utils/SpriteRenderer.h"

class Obstacle : public Actor {
public:
	Obstacle(glm::vec2 aPosition, glm::vec2 aSize, Texture aActorTexture, float aHoleHSize);
	
	void SetObstacleChecked() { IsChecked = true; }
	bool IsObstacleChecked() { return IsChecked; }
	virtual void Draw(SpriteRenderer& Sprite) override;

private:
	bool IsChecked = false;
	float HoleSize;
};