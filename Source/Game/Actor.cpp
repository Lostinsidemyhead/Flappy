#include "Actor.h"

Actor::Actor()
{
	Position = glm::vec2(0.0f, 0.0f);
	Size = glm::vec2(0.0f, 0.0f);
}

Actor::Actor(glm::vec2 aPosition, glm::vec2 aSize, Texture aActorTexture)
{
	Position = aPosition;
	Size = aSize;
	ActorTexture = aActorTexture;
}

void Actor::Move(glm::vec2 Distance)
{
	Position.x += Distance.x;
	Position.y += Distance.y;
}

void Actor::Draw(SpriteRenderer& Sprite)
{
	Sprite.DrawSprite(ActorTexture, Position, Size);
}