#include "Obstacle.h"

Obstacle::Obstacle(glm::vec2 aPosition, glm::vec2 aSize, Texture aActorTexture, float aHoleHeight)
{
	Position = aPosition;
	Size = aSize;
	ActorTexture = aActorTexture;
	HoleHeight = aHoleHeight;
}

void Obstacle::Draw(SpriteRenderer& Sprite)
{
	Sprite.DrawSprite(ActorTexture, Position, Size);


}