#include <GLFW/glfw3.h>
#include "GameDefs.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include <iostream>

GameObject::GameObject()
{
	parent = -1;
	m_position.x = HALF_SCRW;
	m_position.y = HALF_SCRH;
	m_rotation = 0;
}


GameObject::~GameObject()
{
}

void GameObject::Update(float dt, bool a)
{
	if (a == true) {
		//gravity
		if (SCREEN_HEIGHT > GROUND_Y) {
			m_velocity.y -= GRAVITY;
			m_position.y += m_velocity.y * dt / 260000;
		}
	}
	else {
		m_position.x * dt;
		m_position.y * dt;
	}
}

void GameObject::Draw(SpriteBatch* spritebatch)
{
	Matrix3 translate = Matrix3(1, 0, m_position.x, 0, 1, m_position.y, 0, 0, 1);
	Matrix3 rotation;
	rotation.setRotateZ(m_rotation);
	Matrix3 scale = Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1);
	localTransform = scale * rotation * translate;
	if (parent >= 0){
		Matrix3 parentTransform = Application2D::getInstance()->getObjects().at(parent)->getWorldTransform();
		worldTransform = localTransform * parentTransform;
		//localTransform = parentTransform;
		
	}
	else {
		worldTransform = localTransform;
	}


	/*if (mousePosition.x >= 0 && mousePosition.y >= 0)
	{
		spritebatch->drawLine(worldTransform.m[2][0], worldTransform.m[2][1], mousePosition.x, mousePosition.y);
	}*/
	spritebatch->drawSpriteTransformed3x3(m_sprite, worldTransform);
}

void GameObject::seek(std::vector<GameObject*> obj, Vector2 v, Vector2 f, Vector2 h, float dTime)
{
	v.x = obj.at(0)->getPosition().x - obj.at(1)->getPosition().x;
	v.y = obj.at(0)->getPosition().y - obj.at(1)->getPosition().y;
	v.normalise();
	v.x*obj.at(1)->m_Vel();
	v.y*obj.at(1)->m_Vel();

	f = 1000 * v - obj.at(1)->m_velocity;
	//objects.at(1)->setRotate(atan(V.x / V.y));

	obj.at(1)->m_velocity = obj.at(1)->m_velocity + (dTime * f);
	obj.at(1)->m_position.x += (obj.at(1)->m_velocity.x * dTime);
	obj.at(1)->m_position.y += (obj.at(1)->m_velocity.y * dTime);

	h = obj.at(1)->m_velocity;
	h.normalise();
}

void GameObject::flee(std::vector<GameObject*> obj, Vector2 v, Vector2 f, Vector2 h, float dTime)
{
	v.x = obj.at(0)->getPosition().x - obj.at(1)->getPosition().x;
	v.y = obj.at(0)->getPosition().y - obj.at(1)->getPosition().y;
	v.normalise();
	v.x*obj.at(1)->m_Vel();
	v.y*obj.at(1)->m_Vel();

	f = 100 * v - obj.at(1)->m_velocity;
	//objects.at(1)->setRotate(atan(V.x / V.y));

	obj.at(1)->m_velocity = obj.at(1)->m_velocity - (dTime * f);
	obj.at(1)->m_position.x += (obj.at(1)->m_velocity.x * dTime);
	obj.at(1)->m_position.y += (obj.at(1)->m_velocity.y * dTime);

	h = obj.at(1)->m_velocity;
	h.normalise();
}

void GameObject::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void GameObject::setRotate(float x)
{
	m_rotation = x;
}

void GameObject::setLocal()
{

}

void GameObject::setNode(Node* a)
{
	
}



Vector3 GameObject::setScale(Vector3 x)
{
	m_scale = x;
	return Vector3();
}

Vector2 GameObject::getPosition()
{
	return Vector2(m_position.x, m_position.y);
}


float GameObject::getPositionX()
{
	return m_position.x;
}

float GameObject::getPositionY()
{
	return m_position.y;
}

char* GameObject::getXY()
{
	return text;
}

void GameObject::setSprite(std::string filename)
{
	spriteFile = filename;
}

void GameObject::loadSprite()
{
	m_sprite = new Texture(spriteFile.c_str());
}

void GameObject::setAABB(Vector2 min, Vector2 max)
{
	positionMin.x = min.x;
	positionMin.y = min.y;
	positionMax.x = max.x;
	positionMax.y = max.y;
}

void GameObject::setVel(float vel)
{
	Velocity = vel;
}

void GameObject::setmaxVel(float vel_x, float vel_y)
{
	m_velocity.x = vel_x;
	m_velocity.y = vel_y;
}

