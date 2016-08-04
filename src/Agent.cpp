#include "Agent.h"

Agent::Agent()
{
}


Agent::~Agent()
{
}


void Agent::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void Agent::setSprite(std::string filename)
{
	spriteFile = filename;
}

void Agent::loadSprite()
{
	m_sprite = new Texture(spriteFile.c_str());
}