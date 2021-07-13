#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../Utils/Texture.h"
#include "../Utils/SpriteRenderer.h"
#include "../Utils/ResourceManager.h"

class Actor {
public:
	Actor();
	Actor(glm::vec2 aPosition, glm::vec2 aSize, Texture aActorTexture);

	glm::vec2 GetPosition() { return Position; }
	glm::vec2 GetSize() { return Size; }

	virtual void Draw(SpriteRenderer& Sprite);
	virtual void Move(glm::vec2 aNewPosition);

protected:
	glm::vec2 Position, Size;
	Texture ActorTexture;
};
