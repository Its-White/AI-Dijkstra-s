#include "MathsLibrary.h"
#include <string>
#include "Texture.h"
#include "SpriteBatch.h"
#include "Application2D.h"
#pragma once
class Agent
{
public:
	Agent();
	~Agent();

	Vector2 getVel() { return Velocity; };
	Vector2 m_Vel() { return m_velocity; };

	void setPosition(float x, float y);

	void setSprite(std::string filename);	// Set the local filename for the sprite
	void setName(std::string m_name) { name = m_name; };
	std::string getName() { return name; };
	void loadSprite();
	Vector2 getPosition() { return m_position; };

private:
	Texture* m_sprite;
	std::string spriteFile;

	Vector2 Position;
	Vector2 Velocity;
	Vector2 m_velocity;
	Matrix3 localTransform;
	Matrix3 worldTransform;

	Vector2 m_position;

	std::string name;

	float m_rotation;

	int parent;

	float Acceleration;
};

