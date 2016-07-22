#include "Application2D.h"

#include <GLFW/glfw3.h>
#include "Cursor.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "GameDefs.h"
#include "GameObject.h"
#include "Node.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <iterator>
#include <string>
#include <cmath>


double xpos, ypos;
bool inWindow = false;

Cursor cursor;

Application2D* Application2D::m_pInstance = nullptr;

Application2D* Application2D::getInstance()
{
	return m_pInstance;
}

Application2D::Application2D() {
	if (m_pInstance == nullptr)
		m_pInstance = this;
}

Application2D::~Application2D() {

}


bool Application2D::startup() {
	
	createWindow("Maths Graphical App", SCREEN_WIDTH, SCREEN_HEIGHT);

	m_spriteBatch = new SpriteBatch();
	
	m_font = new Font("./bin/font/consolas.ttf", 15);

	Vector2 min;
	Vector2 max;

	//objects = new std::vector<GameObject *>();

	unsigned char pixels[16 * 16 * 4];
	memset(pixels, 0xff, sizeof(pixels));

	GLFWimage c_image;
	c_image.width = 16;
	c_image.height = 16;
	c_image.pixels = pixels;

	GLFWcursor* cursor;
	cursor = glfwCreateCursor(&c_image, 0, 0);


	objects.push_back(new GameObject());
	objects.at(0)->setSprite("./bin/textures/idle_1.png");
	objects.at(0)->setAABB(min, max);
	objects.at(0)->loadSprite();
	objects.at(0)->setPosition((float)HALF_SCRW, (float)HALF_SCRH); //set the players starting position to the center of the screen

	objects.push_back(new GameObject());
	objects.at(1)->setSprite("./bin/textures/bullet.png");
	objects.at(1)->loadSprite();

	objects.push_back(new GameObject());
	objects.at(2)->setSprite("./bin/textures/arm.png");
	objects.at(2)->loadSprite();
	objects.at(2)->setPosition(15, 0);
	objects.at(2)->setRotate(0);		//this value is changed later, it rotates the arm based on the cursor position
	objects.at(2)->setParent(0);		//sets the parent of the arm as the player

	objects.push_back(new GameObject());
	objects.at(3)->setSprite("./bin/textures/enemy.png");
	objects.at(3)->loadSprite();
	objects.at(3)->setPosition(HALF_SCRW, HALF_SCRH);

	objects.push_back(new GameObject());
	objects.at(4)->setSprite("./bin/textures/temp.png");
	objects.at(4)->loadSprite();

	objects.push_back(new GameObject()); 
	objects.at(5)->setSprite("./bin/textures/bg.png");
	objects.at(5)->loadSprite();
	objects.at(5)->setPosition(350, 200);


	m_bPause = true;

	return true;
}


void Application2D::shutdown() {

	delete m_font;
	delete m_spriteBatch;
	//delete m_pPlayer;
	destroyWindow();
}

bool Application2D::update(float deltaTime) {
	

	// close the application if the window closes or we press escape
	if (hasWindowClosed() || isKeyPressed(GLFW_KEY_ESCAPE))
		return false;

	// pause only used at start of the game, can't be toggled during game
	if (m_bPause) {
		if (IsKeyDown(GLFW_KEY_ENTER))
			m_bPause = false;
		return true; 
	}

	glfwGetCursorPos(m_window, &xpos, &ypos);
	Vector2 cursorPos((float)xpos + SCREEN_WIDTH / 2, (float)(SCREEN_HEIGHT - ypos) - SCREEN_HEIGHT / 2);
	Vector2 distanceBetween;
	//Vector2 tempArmWorldPos(objects.at(0)->getWorldTransform()->m[2].x, objects.at(0)->getWorldTransform()->m[2].y);
	distanceBetween = objects.at(0)->getPosition() - cursorPos; //finds the distance between the cursor and the player origin
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//std::cout << "x: " << xpos << " , y: " << ypos << std::endl;

	if (cursorPos.x >= 0 && cursorPos.y >= 0){
		inWindow = true;
	}

	if (IsKeyDown(GLFW_KEY_D)){
		objects.at(0)->setPosition(objects.at(0)->getPositionX() + 150 * deltaTime, objects.at(0)->getPositionY());
	}

	if (IsKeyDown(GLFW_KEY_A)){
		objects.at(0)->setPosition(objects.at(0)->getPositionX() - 150 * deltaTime, objects.at(0)->getPositionY());
	}

	if (cursor.cursor_enter_window(m_window, inWindow, &xpos, &ypos)){
		objects.at(1)->setPosition(cursorPos.x, cursorPos.y);		//sets the position of the cursor
		objects.at(2)->setRotate(atan(distanceBetween.y / distanceBetween.x));		//sets the rotation of the arm based on the pos of the cursor
		//m_spriteBatch->drawLine(objects.at(0)->getPositionX(), objects.at(0)->getPositionY(), xpos, ypos, 1, 0);
		//objects.at(2)->mousePosition = Vector3(xpos, ypos, 1);
		//std::cout << distanceBetween.x << ", " << distanceBetween.y << std::endl;
	}

	if (IsKeyDown(GLFW_KEY_O)) {
		save();  //Using the O key will save the current position of your player so you can load the location of where you were before quitting
	}

	if (IsKeyDown(GLFW_KEY_P)) {
		load();  //Vice versa the P key will load the saved state.
	}

	if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) 
	{

	}

	if (objects.at(0)->getPositionY() > GROUND_Y) {
		objects.at(0)->Update(deltaTime, true);
	}
	objects.at(1)->Update(deltaTime, false);
	return true;
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_spriteBatch->begin();

	if (m_bPause) {
		m_spriteBatch->drawText(m_font, "Press Enter to Start", (float)HALF_SCRW - 200, (float)HALF_SCRH);
	}
	else{
		for (size_t i = 0; i < objects.size(); i++){
			objects.at(i)->Draw(m_spriteBatch);
		}
		if (IsKeyDown(GLFW_KEY_GRAVE_ACCENT)){
			m_spriteBatch->drawText(m_font, "cursor position: ", 10, 10, -1);
			m_spriteBatch->drawText(m_font, "player position: ", 10, 25, -1);
		}
	}

	// done drawing sprites
	m_spriteBatch->end();	
}

void Application2D::save()
{
	std::ofstream outf("save.txt", std::ios::binary);
	outf.write((char*)&objects.at(0)->m_position, sizeof(Vector3));
}

void Application2D::load()
{
	std::ifstream inf("save.txt", std::ios::binary);
	inf.read((char*)&objects.at(0)->m_position, sizeof(Vector3));
}
