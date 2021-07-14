#include "Obstacle.h"

Obstacle::Obstacle(glm::vec2 aPosition, glm::vec2 aSize, Texture aActorTexture, float aHoleSize)
{
	Position = aPosition;
	Size = aSize;
	ActorTexture = aActorTexture;
	HoleSize = aHoleSize;
}

void Obstacle::Draw(SpriteRenderer& Sprite)
{
	Sprite.DrawSprite(ActorTexture, 
		glm::vec2(Position.x, Position.y),
		Size);

	Sprite.DrawSprite(ActorTexture, 
		glm::vec2(Position.x, Position.y - Size.y - HoleSize),
		Size, 180.0f);
}