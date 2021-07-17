#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Actor.h"
#include "Game.h"

class Player : public Actor {
public:
	Player(glm::vec2 aPosition, glm::vec2 aSize, Texture aActorTexture, float aMinBottomPosition);

	void SetMinBottomPosition(float BottomLimit) { MinBottomPosition = BottomLimit; }
	void Up();
	virtual void Move(glm::vec2 NewPosition) override;

private:
	float JumpHeight = 75.0f;
	float JumpSpeedCoef = 1.5f;
	float MinBottomPosition;
	float JumpPosition;
};