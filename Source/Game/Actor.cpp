#include "Actor.h"

Actor::Actor(glm::vec2 aPosition, glm::vec2 aSize, Texture aActorTexture)
{
	Position = aPosition;
	Size = aSize;
	ActorTexture = aActorTexture;
}

void Actor::Draw(SpriteRenderer& Sprite)
{
	Sprite.DrawSprite(ActorTexture, Position, Size);
}