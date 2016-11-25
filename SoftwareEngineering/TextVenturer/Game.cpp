#include "stdafx.h"
#include "TextDisplay.h"
#include "Controler.h"
#include "Player.h"

#include "Game.h"

void Game::updateDeltaTime()
{
    LARGE_INTEGER newTime;
    QueryPerformanceCounter(&newTime);
    deltaTime = (float)(newTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart;
    lastTime = newTime;
}

Game::Game(GLWindow* w)
{
    textShader = new Shader();
    textShader->loadVertFragShader("data/shader/test");
    textShader->addAttribute(2, "vpos");
    textShader->addAttribute(2, "vtexcoord");
    textShader->addAttribute(4, "vcolor");
   
    font = new BMPFont();
    font->loadFromPNG("data/font/font.png");

    //textDisplay = new TextDisplay(textShader, font, 20, 11);
    textDisplay = new TextDisplay(textShader, font, 60, 33);

    controler = new Controler(textDisplay,this);

	player = new Player();
	window = w;

    QueryPerformanceFrequency(&frequency);
    updateDeltaTime();
}    

Game::~Game()
{
    delete textDisplay;
	delete player;
    delete font;
    delete textShader;
}

void Game::update()
{
    updateDeltaTime();

    controler->update(deltaTime);
    textDisplay->update(deltaTime);
}

void Game::render()
{
    textDisplay->render();
}

void Game::resize(int width, int height)
{
    glUniform1f(textShader->getUniformLocation("aspect"), (float)width / height);
}

void Game::pressChar(byte c)
{                             
    controler->pressChar(c);

    string test;
    test.substr();
}

Player* Game::getPlayer() 
{
	return player;
}

GLWindow* Game::getWindow()
{
	return window;
}