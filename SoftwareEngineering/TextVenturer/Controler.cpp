#include "stdafx.h"
#include "TextDisplay.h"
#include "Game.h"
#include "Player.h"
#include "Command.h"

#include "Controler.h"
#include "window.h"

void Controler::updateInput()
{
    for (int x = cursorMin; x < cursorMax; x++)
        textDisplay->write(x, textDisplay->getCursorPos().y, ' ');
    textDisplay->write(cursorMin, textDisplay->getCursorPos().y, input);
}

Controler::Controler(TextDisplay* textDisplay, Game* game)
{
    this->textDisplay = textDisplay;
	this->game = game;
    textDisplay->setCursorVisible(true);
    textDisplay->setCursorPos(ivec2(3, textDisplay->getHeight() - 2));
    cursorMin = 3;
    cursorMax = textDisplay->getWidth() - 2;
}

void Controler::pressChar(byte c)
{
    switch (c)
    {
    case VK_BACK:
        if (textDisplay->getCursorPos().x > cursorMin)
        {
            ivec2 p = textDisplay->getCursorPos();
            p.x--;
            textDisplay->setCursorPos(p);
            textDisplay->resetCursorTime();
            input.resize(input.length() - 1);
            updateInput();
        }
        break;
    case VK_RETURN:
    {
        command(input);

        input = "";
        updateInput();
        textDisplay->setCursorPos(ivec2(cursorMin, textDisplay->getCursorPos().y));

        break;
    }
    case 127: // CTRL-BACK
    {
        ivec2 p = textDisplay->getCursorPos();
        p.x--;
        while (textDisplay->getChar(p) == ' ' && p.x >= cursorMin)
        {
            pressChar(VK_BACK);
            p.x--;
        }
        while (textDisplay->getChar(p) != ' ' && p.x >= cursorMin)
        {
            pressChar(VK_BACK);
            p.x--;
        }
        break;
    }                     
    default:
        if (textDisplay->getCursorPos().x < cursorMax)
        {
            ivec2 p = textDisplay->getCursorPos();
            p.x++;
            textDisplay->setCursorPos(p);
            textDisplay->resetCursorTime();
            input += c;
            updateInput();
        }
    }                   
}

void Controler::update(float deltaTime)
{

}

void Controler::textscrolling(string msg)
{
    for (int j = 0; j < (textDisplay->getHeight() - 3); j++)
    {       
        if (j == (textDisplay->getHeight() - 4))
        {
            textDisplay->write(2, j, msg);
            for (int x = msg.length() + 2; x < textDisplay->getWidth(); x++)
                textDisplay->write(x, j, " ");
        }
        else
        {
            textDisplay->write(0, j, textDisplay->getLine(j + 1));
        }
    }
}

void Controler::command(string msg)
{
    Command help("help");
    help.addAlias("list commands");

    Command hello("hello");
    hello.addAlias("hello!");

    Command clear("clear");
    clear.addAlias("clear screen");
    clear.addAlias("clear display");

    Command pickup("pick up <object>");
    pickup.addAlias("pickup <object>");

    Command inventory("inventory");
    inventory.addAlias("show inventory");

    Command combine("combine <object 1> with <object 2>");
    combine.addAlias("combine <object 1> and <object 2>");

	Command use("use <object 1> with <object 2>");
	combine.addAlias("use <object 1> and <object 2>");

    if (help.check(msg))
	{
        textscrolling("Available Commands:");
        textscrolling(help.getName());
        textscrolling(hello.getName());
        textscrolling(clear.getName());
        textscrolling(pickup.getName());
        textscrolling(inventory.getName());
        textscrolling(combine.getName());  
	}
	else if (hello.check(msg))
	{
        textscrolling("Hey there!");
	}
    else if (clear.check(msg))
	{
		textDisplay->clear();
	}
    else if (Command::Result params = pickup.check(msg))
	{
		game->getPlayer()->additem(params["object"]);
        textscrolling("Picked up " + params["object"]);
	}
	else if (inventory.check(msg))
	{
        textscrolling("Your inventory contains:");
		int y = 4;
        textscrolling("");
		vector<string> inventory = game->getPlayer()->getInventory();
	    for (string item : inventory)
            textscrolling(item);
	}
    else if (Command::Result params = combine.check(msg))
	{
        textscrolling("Combining " + params["object 1"] + " and " + params["object 2"] + " with a lot of magic!");
	}
	else if (Command::Result params = use.check(msg))
	{
		textscrolling("Used " + params["object 1"] + " with " + params["object 2"] + " and nothing happends.");
	}
	else
	{
        textscrolling("Wait... what?");
	}
}
