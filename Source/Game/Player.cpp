#include "Player.h"

Player::Player(glm::vec2 aPosition, glm::vec2 aSize, Texture aActorTexture, float aMinBottomPosition)
{
	Position = aPosition;
	Size = aSize;
	ActorTexture = aActorTexture;
	MinBottomPosition = aMinBottomPosition;
	JumpPosition = aMinBottomPosition;
}

void Player::Up()
{
	JumpPosition = Position.y - JumpHeight;
}

void Player::Move(glm::vec2 Distance)
{
	if (Position.y > JumpPosition)
	{
		Position.y -= Distance.y;
	}
	else
	{
		JumpPosition = MinBottomPosition;
		Actor::Move(Distance);
	}
}