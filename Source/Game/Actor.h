#ifndef ACTOR_H
#define ACTOR_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../Utils/Texture.h"
#include "../Utils/SpriteRenderer.h"
#include "../Utils/ResourceManager.h"

class Actor
{
public:
	glm::vec2 Position, Size;
	Texture ActorTexture;

	Actor(glm::vec2 aPosition, glm::vec2 aSize, Texture aSprite);

	void Move();
	void Draw(SpriteRenderer& Sprite);
	//void GetVelocity() { return Velocity; }

private:
	float Velocity;
};

#endif