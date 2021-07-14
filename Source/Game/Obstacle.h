#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Actor.h"
#include "../Utils/ResourceManager.h"
#include "../Utils/SpriteRenderer.h"

class Obstacle : public Actor {
public:
	Obstacle(glm::vec2 aPosition, glm::vec2 aSize, Texture aActorTexture, float aHoleHSize);
	
	virtual void Draw(SpriteRenderer& Sprite) override;

private:
	float HoleSize;
};